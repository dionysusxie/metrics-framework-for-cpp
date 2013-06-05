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

bool MetricsSystem::registerSource(boost::shared_ptr<source::MetricsSource>) {
    return true;
}

bool MetricsSystem::registerSink(boost::shared_ptr<sink::MetricsSink>) {
    return true;
}

void MetricsSystem::start() {

}

void MetricsSystem::stop() {

}

} /* namespace gmf */
