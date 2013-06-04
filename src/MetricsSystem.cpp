/*
 * MetricsSystem.cpp
 *
 *  Created on: Jun 4, 2013
 *      Author: xieliang
 */

#include "MetricsSystem.h"

using namespace boost;

namespace gmf {

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

} /* namespace gmf */
