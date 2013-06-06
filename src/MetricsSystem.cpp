/*
 * MetricsSystem.cpp
 *
 *  Created on: Jun 4, 2013
 *      Author: xieliang
 */

#include "MetricsSystem.h"

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

bool MetricsSystem::config() {
    return true;
}

// @param  src  A ptr to metrics-source to be registered.
// @return  true if registered OK, otherwise false.
// @note  If the name of the source to be registered already exists, false returned.
bool MetricsSystem::registerSource(source::MetricsSourcePtr src) {
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

bool MetricsSystem::registerSink(boost::shared_ptr<sink::MetricsSink>) {
    return true;
}

void MetricsSystem::start() {
    METRICS_LOG_INFO("system start");
}

void MetricsSystem::stop() {

}

} /* namespace gmf */
