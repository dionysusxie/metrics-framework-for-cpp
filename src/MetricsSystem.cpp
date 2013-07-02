/*
 * MetricsSystem.cpp
 *
 *  Created on: Jun 4, 2013
 *      Author: xieliang
 */

#include "MetricsSystem.h"
#include "conf.h"

using namespace std;
using namespace boost;

namespace gmf {

static const string TXT_COLLECT_INTERVAL = "collect_interval";
static const unsigned long DEF_METRICS_COLLECTING_INTERVAL = 10;
static const string COLLECTING_THREAD_NAME = "Metrics-Collecting-Thread";

static void threadStatic(MetricsSystem* ptr) {
    return ptr->threadFunc();
}


// initialize the static member variables:
shared_ptr<MetricsSystem> MetricsSystem::s_pSingleton;

shared_ptr<MetricsSystem> MetricsSystem::getSingleton() {
    if (NULL == s_pSingleton.get()) {
        s_pSingleton.reset(new MetricsSystem());
    }

    return s_pSingleton;
}

MetricsSystem::MetricsSystem() {
}

MetricsSystem::~MetricsSystem() {
}

bool MetricsSystem::config(StoreConf_SPtr conf) {
    boost::lock_guard<recursive_timed_mutex> lock(this->common_mutex_);
    METRICS_LOG_INFO("Begin to config the metrics system");

    // pre-assertions:
    {
        BOOST_ASSERT_MSG(conf.get() != NULL, "Null config found in MetricsSystem::config()");
    }

    // If the collecting thread existed, return false!
    if (this->metrics_collecting_thread_.get() != NULL) {
        METRICS_LOG_ERROR("The metrics collecting thread is already running! You can't config it now.");
        return false;
    }

    // config the thread to collecting metrics snapshot
    {
        // collecting interval
        this->metrics_collecting_interval_ = DEF_METRICS_COLLECTING_INTERVAL;
        conf->getUnsigned(TXT_COLLECT_INTERVAL, this->metrics_collecting_interval_);
        METRICS_LOG_INFO("%s: %s = %u", COLLECTING_THREAD_NAME.c_str(),
                TXT_COLLECT_INTERVAL.c_str(), this->metrics_collecting_interval_);
    }

    // register sinks
    {
        std::vector<StoreConf_SPtr> conf_stores;
        conf->getAllStores(conf_stores);

        for (vector<StoreConf_SPtr>::iterator it = conf_stores.begin();
                it != conf_stores.end(); it++) {
            StoreConf_SPtr conf_item = *it;

            bool is_sink = false;
            {
                const string store_name = conf_item->getName();
                is_sink = store_name.find(TXT_SINK) == 0;
            }

            if (is_sink) {
                this->registerSink(sink::MetricsSink::createSink(conf_item));
            }
        }
    }

    return true;
}

// @param  src  A ptr to metrics-source to be registered.
// @return  true if registered OK, otherwise false.
// @note  If the name of the source to be registered already exists, false returned.
bool MetricsSystem::registerSource(source::MetricsSourcePtr src) {
    boost::lock_guard<recursive_timed_mutex> lock(this->common_mutex_);

    // If the collecting thread existed, return false!
    if (this->metrics_collecting_thread_.get() != NULL) {
        METRICS_LOG_ERROR("The metrics collecting thread is already running! You can't config it now.");
        return false;
    }

    if (src.get() == NULL) {
        const string err("NULL ptr of the metrics-source to be registered!");
        METRICS_LOG_WARNING(err);
        BOOST_ASSERT_MSG(false, err.c_str());
        return false;
    }

    bool registered_already = this->sources_.count(src->getName()) > 0;
    if (registered_already) {
        string err;
        {
            ostringstream os;
            os << "Source <" << src->getName() << "> already registered!";
            err = os.str();
        }

        METRICS_LOG_WARNING(err);
        BOOST_ASSERT_MSG(false, err.c_str());
        return false;
    }

    this->sources_[src->getName()] = src;
    METRICS_LOG_INFO("Register source %s: %s", src->getName().c_str(), src->getDescription().c_str());
    return true;
}

bool MetricsSystem::registerSink(sink::MetricsSinkPtr sink) {
    boost::lock_guard<recursive_timed_mutex> lock(this->common_mutex_);

    if (sink.get() == NULL) {
        METRICS_LOG_WARNING("NULL ptr of the metrics-sink to be registered");
        return false;
    }

    bool registered_already = this->sinks_.count(sink->getName()) > 0;
    if (registered_already) {
        METRICS_LOG_WARNING("Sink with the name %s already registered", sink->getName().c_str());
        return false;
    }

    this->sinks_[sink->getName()] = sink;
    return true;
}

void MetricsSystem::start() {
    boost::lock_guard<recursive_timed_mutex> lock(this->common_mutex_);

    // If the collecting thread existed, return!
    if (this->metrics_collecting_thread_.get() != NULL) {
        METRICS_LOG_ERROR("The metrics collecting thread is already running! You can't config it now.");
        BOOST_ASSERT(false);
        return;
    }

    // start the thread
    METRICS_LOG_INFO("system start ...");
    this->metrics_collecting_thread_ = shared_ptr<thread>(new thread(threadStatic, this));
}

void MetricsSystem::stop() {
    boost::lock_guard<recursive_timed_mutex> lock(this->common_mutex_);

    METRICS_LOG_INFO("system stop ...");


    //
    // stop the thread of collecting metrics
    //

    if (this->metrics_collecting_thread_.get() == NULL) {
        METRICS_LOG_WARNING("%s: already stopped", COLLECTING_THREAD_NAME.c_str());
    }
    else {
        // put a command of ending
        {
            lock_guard<mutex> guard(this->thread_cmds_mutex_);
            this->thread_cmds_.push(CMD_STOP);
            METRICS_LOG_INFO("%s: put a command of CMD_STOP", COLLECTING_THREAD_NAME.c_str());
        }

        // awake the sleeping thread
        // oh, we don't have to do it now!

        // wait for the ending of the thread
        {
            this->metrics_collecting_thread_->join();
            METRICS_LOG_INFO("%s: thread stopped", COLLECTING_THREAD_NAME.c_str());
        }

        // clear
        {
            this->metrics_collecting_thread_.reset();
            while (!(this->thread_cmds_.empty())) {
                this->thread_cmds_.pop();
            }
        }
    }


    // clear sources
    {
        this->sources_.clear();
    }

    // stop sinks
    {
        for (SINK_CONTAINER_T::iterator it = this->sinks_.begin();
                it != this->sinks_.end(); it++) {
            it->second->close();
        }

        this->sinks_.clear();
    }
}

void MetricsSystem::threadFunc() {
    METRICS_LOG_INFO("%s: starting ...", COLLECTING_THREAD_NAME.c_str());

    time_t last_work_time = time(NULL);
    bool b_stop = false;
    while(true) {

        //
        // Handle commands
        //

        {
            lock_guard<mutex> lock(thread_cmds_mutex_);

            while (!thread_cmds_.empty()) {
                EnumCommand cmd = thread_cmds_.front();
                thread_cmds_.pop();

                switch (cmd) {
                case CMD_STOP:
                    b_stop = true;
                    break;

                default:
                    METRICS_LOG_ERROR("%s: invalid command found: %u", COLLECTING_THREAD_NAME.c_str(), cmd);
                    break;
                }
            }
        }

        if (b_stop) {
            break;
        }


        //
        // Is time to work?
        //

        bool is_time_to_work = false;
        {
            time_t now = time(NULL);

            // Has the system time been reset to a earlier time?
            if (now < last_work_time) {
                last_work_time = now;
            }
            BOOST_ASSERT(now - last_work_time >= 0);

            const unsigned long time_passed_since_last_work = static_cast<unsigned long>(now - last_work_time);
            is_time_to_work = (time_passed_since_last_work >= this->metrics_collecting_interval_);
        }


        //
        // collect metrics from all registered sources, then push to registered sinks
        //

        if (is_time_to_work) {
            METRICS_LOG_DEBUG("%s: collect metrics snapshot", COLLECTING_THREAD_NAME.c_str());

            // get temporary copys of sources & sinks
            SOURCE_CONTAINER_T tmp_sources;
            SINK_CONTAINER_T tmp_sinks;
            {
                boost::lock_guard<recursive_timed_mutex> lock(this->common_mutex_);
                tmp_sources = this->sources_;
                tmp_sinks = this->sinks_;
            }

            // collect metrics snapshot
            std::vector<ConstMetricsRecordPtr> records;
            {
                for (SOURCE_CONTAINER_T::iterator it = tmp_sources.begin();
                        it != tmp_sources.end(); it++) {
                    records.push_back(it->second->getMetrics());
                }
            }

            // push to sinks
            for (SINK_CONTAINER_T::iterator it = tmp_sinks.begin();
                    it != tmp_sinks.end(); it++) {
                it->second->putMetrics(records);
            }

            // update work time
            last_work_time = time(NULL);
        }


        sleep(1); // sleep for 1 second every time!
    }

    METRICS_LOG_INFO("%s: stop ...", COLLECTING_THREAD_NAME.c_str());
}

} /* namespace gmf */
