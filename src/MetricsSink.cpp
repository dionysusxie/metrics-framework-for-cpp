/*
 * MetricsSink.cpp
 *
 *  Created on: Jun 4, 2013
 *      Author: xieliang
 */

#include <iostream>
#include "MetricsSink.h"


using namespace std;
using namespace boost;


namespace gmf {
namespace sink {

static const string TXT_MAX_QUEUE_SIZE = "max_queue_size";
static const unsigned long DEF_MAX_QUEUE_SIZE = 100;
static const long SEC_TO_WAIT_FOR_FILL_SINK_QUEUE = 1;


/* static */ MetricsSinkPtr MetricsSink::createSink(StoreConf_SPtr conf) {
    MetricsSinkPtr NULL_PTR;

    string type;
    conf->getString("type", type);
    METRICS_LOG_INFO("Create sink: type = %s", type.c_str());

    MetricsSinkPtr sink;
    if (SinkToConsole::TYPE_TXT == type) {
        sink.reset(new SinkToConsole());
    }
    else {
        const string fail_msg = "Invalid sink type: " + type;
        METRICS_LOG_ERROR(fail_msg);
        BOOST_ASSERT_MSG(false, fail_msg.c_str());
        return NULL_PTR;
    }

    sink->config(conf);

    return sink;
}

static void threadStatic(MetricsSink* ptr) {
    ptr->threadFunc();
}

MetricsSink::MetricsSink(const std::string& type):
    BasicItem(),
    type_(type) {
    this->has_work_ = false;
}

MetricsSink::~MetricsSink() {
}

std::string MetricsSink::getType() {
    boost::lock_guard<recursive_timed_mutex> lock(this->public_mutex_);
    return this->type_;
}

void MetricsSink::config(StoreConf_SPtr conf) {
    // pre-assertions
    {
        BOOST_ASSERT_MSG(conf.get() != NULL, "Null ptr in MetricsSink::config() found!");
    }

    // get lock first
    boost::lock_guard<recursive_timed_mutex> lock(this->public_mutex_);

    // You can config it only when the sink thread has been stopped.
    if (this->sink_thread_.get() != NULL) {
        string err;
        {
            ostringstream os;
            os << "You can config " << this->getName() << " only when its thread has been stopped";
            err = os.str();
        }

        METRICS_LOG_ERROR(err);
        BOOST_ASSERT_MSG(false, err.c_str());
        return;
    }

    // config self
    {
        this->setName(conf->getName());

        this->max_queue_size_ = DEF_MAX_QUEUE_SIZE;
        conf->getUnsigned(TXT_MAX_QUEUE_SIZE, this->max_queue_size_);

        METRICS_LOG_INFO("%s: %s = %u", this->getName().c_str(),
                TXT_MAX_QUEUE_SIZE.c_str(), this->max_queue_size_);
    }

    // config the derived class
    this->configImpl(conf);

    // start the sink thread
    this->sink_thread_ = shared_ptr<thread>(new thread(threadStatic, this));
}

void MetricsSink::close() {
    boost::lock_guard<recursive_timed_mutex> lock(this->public_mutex_);

    // already closed?
    if (this->sink_thread_.get() == NULL) {
        METRICS_LOG_WARNING("You are closing the sink %s which is already closed.", this->getName().c_str());
        return;
    }

    // stop the sink thread first
    {
        // put a command of ending
        {
            lock_guard<mutex> guard(this->thread_cmds_mutex_);
            this->thread_cmds_.push(CMD_STOP);
            METRICS_LOG_INFO("%s: put a command of CMD_STOP", this->getName().c_str());
        }

        // awake the sleeping thread
        {
            lock_guard<mutex> guard(this->has_work_mutex_);
            if (!(this->has_work_)) {
                this->has_work_ = true;
                this->has_work_cond_.notify_all();
                METRICS_LOG_INFO("%s: awake the sleeping thread", this->getName().c_str());
            }
        }

        // wait for the ending of the sink thread
        {
            this->sink_thread_->join();
            METRICS_LOG_INFO("%s: thread stopped", this->getName().c_str());
        }

        // clear the flag
        {
            this->sink_thread_.reset();
            this->record_queue_.reset();
        }
    }

    // close the derived class
    {
        closeImpl();
    }

    // post-assertsions
    {
        BOOST_ASSERT(this->sink_thread_.get() == NULL);
    }
}

// @note  Don't change anything in param 'records', for it will be pushed to other sinks.
void MetricsSink::putMetrics(const std::vector<ConstMetricsRecordPtr>& records) {
    // get the lock with time-out!
    boost::unique_lock<boost::recursive_timed_mutex> timed_lock(this->public_mutex_,
            boost::get_system_time() + boost::posix_time::seconds(SEC_TO_WAIT_FOR_FILL_SINK_QUEUE));
    if (!timed_lock.owns_lock()) {
        METRICS_LOG_WARNING("Failed to fill metrics records to sink %s! Can't get lock in %d seconds.",
                this->getName().c_str(), SEC_TO_WAIT_FOR_FILL_SINK_QUEUE);
        return;
    }


    // add records to the queue
    {
        lock_guard<mutex> guard(this->queue_lock_);

        if (this->record_queue_.get() == NULL) {
            this->record_queue_.reset(new RECORDS_QUEUE);
        }

        METRICS_LOG_DEBUG("%s: queue size %u, new records %u", this->getName().c_str(),
                this->record_queue_->size(), records.size());

        for (size_t i = 0; i < records.size(); i++) {
            if (this->record_queue_->size() >= this->max_queue_size_) {
                const size_t num_lost_records = records.size() - i;
                METRICS_LOG_WARNING("%s: queue is full, %u records lost",
                        this->getName().c_str(), num_lost_records);
                break;
            }

            this->record_queue_->push(records[i]);
        }
    }

    // awake the sink thread
    {
        lock_guard<mutex> guard(this->has_work_mutex_);
        if (!(this->has_work_)) {
            this->has_work_ = true;
            this->has_work_cond_.notify_all();
        }
    }
}

void MetricsSink::threadFunc() {
    METRICS_LOG_INFO("%s: sink thread starting ...", this->getName().c_str());

    bool b_stop = false;
    while(true) {

        // Handle commands
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
                    METRICS_LOG_ERROR("%s: invalid command type: %u", this->getName().c_str(), cmd);
                    break;
                }
            }
        }

        if (b_stop) {
            break;
        }

        // consume the records
        {
            RECORDS_QUEUE_PTR tmp_queue;
            {
                lock_guard<mutex> guard(this->queue_lock_);
                tmp_queue = this->record_queue_;
                this->record_queue_.reset(new RECORDS_QUEUE());
            }

            if (tmp_queue.get() != NULL) {
                METRICS_LOG_DEBUG("%s: begin to consume the metrics records", this->getName().c_str());
                this->consumeRecords(tmp_queue);
            }
        }

        // sleep if no work to do
        {
            lock_guard<mutex> guard(this->has_work_mutex_);
            if (!this->has_work_) {
                this->has_work_cond_.wait(this->has_work_mutex_);
                this->has_work_ = false;
            }
        }
    }

    METRICS_LOG_INFO("%s: sink thread stop ...", this->getName().c_str());
}


//////////////////////////////////////////////////////////////////////////////////////////
//
// class SinkToConsole:
//

const string SinkToConsole::TYPE_TXT = "console";

SinkToConsole::SinkToConsole():
        MetricsSink(TYPE_TXT) {
}

void SinkToConsole::configImpl(StoreConf_SPtr conf) {

}

void SinkToConsole::closeImpl() {
    METRICS_LOG_INFO("%s: close %s", this->getName().c_str(), TYPE_TXT.c_str());
}

// Write records to std.
void SinkToConsole::consumeRecords(RECORDS_QUEUE_PTR records) {
    if (records.get() == NULL) {
        METRICS_LOG_DEBUG("Null pointer encountered in SinkToConsole::consumeRecords()");
        return;
    }

    while (!records->empty()) {
        ConstMetricsRecordPtr r = records->front();

        string out_line;
        {
            ostringstream os;

            os << r->getTimestamp() << "  " << r->getName() << "." << r->getContext()
               << ", " << r->getDescription() << "; ";

            // add tags
            {
                gmf::MetricsRecord::TAGS_MAP_T tags = r->getTags();
                for (gmf::MetricsRecord::TAGS_MAP_T::const_iterator it = tags.begin();
                        it != tags.end(); it++) {
                    const string tag_name = it->second.getName();
                    const string tag_value = it->second.getValue();
                    os << tag_name << "=" << tag_value << ", ";
                }
            }

            out_line = os.str();
        }

        cout << out_line << endl;
        records->pop();
    }
}

} /* namespace sink */
} /* namespace gmf */
