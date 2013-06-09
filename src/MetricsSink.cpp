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

/* static */ MetricsSinkPtr MetricsSink::createSink(StoreConf_SPtr conf) {
    MetricsSinkPtr NULL_PTR;

    string type;
    conf->getString("type", type);

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
    type_(type) {
    // TODO Auto-generated constructor stub

}

MetricsSink::~MetricsSink() {
    // TODO Auto-generated destructor stub
}

std::string MetricsSink::getType() {
    boost::lock_guard<recursive_timed_mutex> lock(this->public_mutex_);
    return this->type_;
}

std::string MetricsSink::getName() {
    boost::lock_guard<recursive_timed_mutex> lock(this->public_mutex_);
    return this->name_;
}

void MetricsSink::config(StoreConf_SPtr conf) {
    // pre-assertions
    {
        BOOST_ASSERT_MSG(conf.get() != NULL, "Null ptr in MetricsSink::config() found!");
    }

    // get lock first
    boost::lock_guard<recursive_timed_mutex> lock(this->public_mutex_);

    // You can config it only the sink thread has been stopped.
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
        this->name_ = conf->getName();
        METRICS_LOG_INFO("sink %s:", this->name_.c_str());

        this->max_queue_size_ = DEF_MAX_QUEUE_SIZE;
        conf->getUnsigned(TXT_MAX_QUEUE_SIZE, this->max_queue_size_);
        METRICS_LOG_INFO("%s = %u", TXT_MAX_QUEUE_SIZE.c_str(), this->max_queue_size_);
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
        METRICS_LOG_WARNING("You are closing a sink %s which is already closed.", this->getName().c_str());
        return;
    }

    // close the derived class first
    {
        closeImpl();
    }

    // stop the sink thread
    {

    }
}

void MetricsSink::putMetrics(std::vector<MetricsRecordPtr> records) {
    boost::lock_guard<recursive_timed_mutex> lock(this->public_mutex_);
}

void MetricsSink::threadFunc() {
//    METRICS_LOG_INFO("%s: sink thread starting ...", this->name_.c_str());
//
//
//    //
//    // the loop:
//    //
//
//    bool b_stop = false;
//    while (!b_stop) {
//
//        // Handle commands
//        {
//            lock_guard<mutex> lock(thread_cmds_mutex_);
//
//            while (!thread_cmds_.empty()) {
//                EnumCommand cmd = thread_cmds_.front();
//                thread_cmds_.pop();
//
//                switch (cmd) {
//                case CMD_STOP:
//                    b_stop = true;
//                    break;
//                default:
//                    LOG_WARNING("Invalid command type!");
//                    break;
//                }
//            }
//        }
//
//
//        //
//        // publish now!
//        //
//
//        // Convert data in the container to JSON string for sending out.
//        if (jsons_for_sending_.empty()) {
//            ContainerType tmp_container;
//            {
//                lock_guard<shared_mutex> write_lock(container_mutex_);
//                tmp_container.swap(container_);
//            }
//
//            convertStatisticsToJSONStr(tmp_container, jsons_for_sending_, MAX_NUM_ITEMS_TO_PUBLISH_EACH_TIME);
//        }
//
//        if (sendJSONData(jsons_for_sending_, zmq_socket)) {
//            // update the timestamp of last sending OK
//            {
//                lock_guard<shared_mutex> write_lock(lock_of_the_timestamp_of_last_sending_ok_);
//                timestamp_of_last_sending_ok_ = time(NULL);
//            }
//
//            usleep(SLEEP_TIME_IN_USECONDS_WHEN_SUCCEED);
//        }
//        else {
//            usleep(SLEEP_TIME_IN_USECONDS_WHEN_FAILED);
//        }
//
//
//        //
//        // check subscribing of Giant Dimension update
//        //
//
//        if (subscribe_gd_ && (!b_stop)) {
//            Schema_SubmittedGDVals_Map_Ptr gdvals = getSubscribedGDSubmittedVals(gd_subscriber);
//            if (gdvals) {
//                if (updateGiantDimensionVals(*gdvals)) {
//                    LOG_DEBUG("Giant Dimension Update: successfully");
//                }
//                else {
//                    LOG_INFO("Giant Dimension Update: failed");
//                }
//            }
//        }
//    }
//
//    LOG_INFO("The publishing thread begin to end now ...");
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

}

// Write records to std.
void SinkToConsole::consumeRecords(std::queue<MetricsRecordPtr> records) {
    while (!records.empty()) {
        MetricsRecordPtr r = records.front();

        string out_line;
        {
            out_line = r->getTimestamp() + "  " + r->getName() + "." + r->getContext() +
                    ", " + r->getDescription();
        }
        cout << out_line << endl;

        records.pop();
    }
}

} /* namespace sink */
} /* namespace gmf */
