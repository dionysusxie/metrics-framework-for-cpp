/*
 * MutableMetric.cpp
 *
 *  Created on: Jun 20, 2013
 *      Author: xieliang
 */

#include "MutableMetric.h"

namespace gmf {

//////////////////////////////////////////////////////////////////////////////////////////
//
// class MutableMetric:
//

MutableMetric::MutableMetric(const BasicItemReadOnly& info):
        BasicItem(info),
        changed_(true) {
}

MutableMetric::~MutableMetric() {
}

// all: if true, snapshot unchanged metrics as well
void MutableMetric::snapshot(MetricsRecordBuilder& builder, bool all) {
    if (all || this->changed()) {
        snapshotImpl(builder);
        this->clearChanged();
    }
}

void MutableMetric::snapshot(MetricsRecordBuilder& builder) {
    this->snapshot(builder, false);
}

bool MutableMetric::changed() {
    boost::shared_lock<boost::shared_mutex> read_lock(this->changed_mutex_);
    return this->changed_;
}

void MutableMetric::setChanged() {
    boost::lock_guard<boost::shared_mutex> write_lock(this->changed_mutex_);
    this->changed_ = true;
}

void MutableMetric::clearChanged() {
    boost::lock_guard<boost::shared_mutex> write_lock(this->changed_mutex_);
    this->changed_ = false;
}


//////////////////////////////////////////////////////////////////////////////////////////
//
// class MutableCounter:
//

MutableCounter::MutableCounter(const BasicItemReadOnly& info):
        MutableMetric(info) {
}

void MutableCounter::incr() {
    boost::lock_guard<boost::shared_mutex> write_lock(this->value_mutex_);
    this->incrImpl();
    this->setChanged();
}

void MutableCounter::incr(number::Number_CRef delta) {
    boost::lock_guard<boost::shared_mutex> write_lock(this->value_mutex_);
    this->incrImpl(delta);
    this->setChanged();
}

number::NumberPtr MutableCounter::getValue() {
    boost::shared_lock<boost::shared_mutex> read_lock(this->value_mutex_);
    return this->getValueImpl();
}


//////////////////////////////////////////////////////////////////////////////////////////
//
// class MutableCounterInt:
//

MutableCounterInt::MutableCounterInt(const BasicItemReadOnly& info, int init_value):
        MutableCounter(info),
        value_(init_value) {
}

void MutableCounterInt::incrImpl() {
    this->value_++;
}

void MutableCounterInt::incrImpl(number::Number_CRef delta) {
    this->value_ += delta.intValue();
}

number::NumberPtr MutableCounterInt::getValueImpl() {
    return number::NumberPtr(new number::Int(this->value_));
}

void MutableCounterInt::snapshotImpl(MetricsRecordBuilder& builder) {
}


//////////////////////////////////////////////////////////////////////////////////////////
//
// class MutableCounterLong:
//

MutableCounterLong::MutableCounterLong(const BasicItemReadOnly& info, long init_value):
        MutableCounter(info),
        value_(init_value) {
}

void MutableCounterLong::incrImpl() {
    this->value_++;
}

void MutableCounterLong::incrImpl(number::Number_CRef delta) {
    this->value_ += delta.longValue();
}

number::NumberPtr MutableCounterLong::getValueImpl() {
    return number::NumberPtr(new number::Long(this->value_));
}

void MutableCounterLong::snapshotImpl(MetricsRecordBuilder& builder) {
}

} /* namespace gmf */









