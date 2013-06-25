/*
 * AbstractMetric.cpp
 *
 *  Created on: May 30, 2013
 *      Author: xieliang
 */

#include "MetricSnapshot.h"

namespace gmf {

std::ostream& operator << (std::ostream& os, const MetricSnapshot& m) {
    os << "(" << m.getName() << "," << m.getType() << "," << (*m.getValue()) << ")";
    return os;
}


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


//////////////////////////////////////////////////////////////////////////////////////////
//
// class MetricGauge:
//

MetricGauge::MetricGauge(const BasicItemReadOnly& info):
        MetricSnapshot(info) {
}

MetricType MetricGauge::getType() const {
    return gmf::GAUGE;
}


//////////////////////////////////////////////////////////////////////////////////////////
//
// class MetricGaugeInt:
//

MetricGaugeInt::MetricGaugeInt(const BasicItemReadOnly& info, int init_val):
        MetricGauge(info),
        value_(init_val) {
}

number::NumberPtr MetricGaugeInt::getValue() const {
    number::NumberPtr val(new number::Int(this->value_));
    return val;
}


//////////////////////////////////////////////////////////////////////////////////////////
//
// class MetricGaugeLong:
//

MetricGaugeLong::MetricGaugeLong(const BasicItemReadOnly& info, long init_val):
        MetricGauge(info),
        value_(init_val) {
}

number::NumberPtr MetricGaugeLong::getValue() const {
    number::NumberPtr val(new number::Long(this->value_));
    return val;
}

} /* namespace gmf */
