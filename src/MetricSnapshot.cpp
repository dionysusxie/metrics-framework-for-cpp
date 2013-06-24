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

MetricSnapshot::MetricSnapshot(const BasicItemReadOnly& info):
        BasicItemReadOnly(info) {
}

MetricSnapshot::~MetricSnapshot() {
}


//////////////////////////////////////////////////////////////////////////////////////////
//
// class MetricCounterInt:
//

MetricCounterInt::MetricCounterInt(const BasicItemReadOnly& info, int val):
        MetricSnapshot(info),
        value_(val) {
}

MetricType MetricCounterInt::getType() const {
    return gmf::COUNTER;
}

number::NumberPtr MetricCounterInt::getValue() const {
    number::NumberPtr val(new number::Int(this->value_));
    return val;
}


//////////////////////////////////////////////////////////////////////////////////////////
//
// class MetricCounterLong:
//

MetricCounterLong::MetricCounterLong(const BasicItemReadOnly& info, long val):
        MetricSnapshot(info),
        value_(val) {
}

MetricType MetricCounterLong::getType() const {
    return gmf::COUNTER;
}

number::NumberPtr MetricCounterLong::getValue() const {
    number::NumberPtr val(new number::Long(this->value_));
    return val;
}

} /* namespace gmf */
