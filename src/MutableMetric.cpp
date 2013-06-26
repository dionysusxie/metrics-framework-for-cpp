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

} /* namespace gmf */
