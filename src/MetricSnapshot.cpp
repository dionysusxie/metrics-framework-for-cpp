/*
 * AbstractMetric.cpp
 *
 *  Created on: May 30, 2013
 *      Author: xieliang
 */

#include "MetricSnapshot.h"

namespace gmf {

//////////////////////////////////////////////////////////////////////////////////////////
//
// class MetricSnapshot:
//

MetricSnapshot::MetricSnapshot(const std::string& name, const std::string& desc):
        BasicItemReadOnly(name, desc) {
}

MetricSnapshot::~MetricSnapshot() {
}


//////////////////////////////////////////////////////////////////////////////////////////
//
// class MetricCounterInt:
//

MetricCounterInt::MetricCounterInt(int val, const std::string& name, const std::string& desc):
        MetricSnapshot(name, desc),
        value_(val) {
}

MetricType
MetricCounterInt::getType() const {
    return gmf::COUNTER;
}

number::Number_CRef
MetricCounterInt::getValue() const {
    return this->value_;
}


//////////////////////////////////////////////////////////////////////////////////////////
//
// class MetricCounterLong:
//

MetricCounterLong::MetricCounterLong(long val, const std::string& name, const std::string& desc):
        MetricSnapshot(name, desc),
        value_(val) {
}

MetricType
MetricCounterLong::getType() const {
    return gmf::COUNTER;
}

number::Number_CRef
MetricCounterLong::getValue() const {
    return this->value_;
}

} /* namespace gmf */
