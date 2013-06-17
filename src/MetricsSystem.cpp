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

// initialize the static member variables:
shared_ptr<MetricsSystem> MetricsSystem::s_pSingleton;

shared_ptr<MetricsSystem> MetricsSystem::getSingleton() {
    if (NULL == s_pSingleton.get()) {
        s_pSingleton.reset(new MetricsSystem());
    }

    return s_pSingleton;
}

MetricsSystem::MetricsSystem() {
    // TODO Auto-generated constructor stub

}

MetricsSystem::~MetricsSystem() {
    // TODO Auto-generated destructor stub
}

bool MetricsSystem::config(StoreConf_SPtr conf) {
    boost::lock_guard<recursive_timed_mutex> lock(this->common_mutex_);
    METRICS_LOG_INFO("Begin to cofig the metrics system");

    if (conf.get() == NULL) {
        return false;
    }

    // get sinks
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

    if (src.get() == NULL) {
        METRICS_LOG_WARNING("NULL ptr of the metrics-source to be registered");
        return false;
    }

    bool registered_already = this->sources_.count(src->getName()) > 0;
    if (registered_already) {
        METRICS_LOG_WARNING("Source with the name %s already registered", src->getName().c_str());
        return false;
    }

    this->sources_[src->getName()] = src;
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
    METRICS_LOG_INFO("system start ...");
}

void MetricsSystem::stop() {
    boost::lock_guard<recursive_timed_mutex> lock(this->common_mutex_);
    METRICS_LOG_INFO("system stop ...");

    // stop the thread of collecting metrics
    {

    }

    // stop sinks
    {
        for (SINK_CONTAINER_T::iterator it = this->sinks_.begin();
                it != this->sinks_.end(); it++) {
            it->second->close();
        }
    }
}

} /* namespace gmf */
