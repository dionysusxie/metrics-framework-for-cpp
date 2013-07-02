/*
 * MetricsRecord.cpp
 *
 *  Created on: May 27, 2013
 *      Author: xieliang
 */

#include "MetricsRecord.h"

using namespace std;
using namespace boost;

namespace gmf {

//////////////////////////////////////////////////////////////////////////////////////////
//
// class MetricsRecord:
//

MetricsRecord::MetricsRecord(const BasicItemReadOnly& info, const string& ctx,
        time_t t, const TAG_VECTOR& tags, const METRIC_SNAPSHOT_VEC& metric_snapshots):
        BasicItemReadOnly(info),
        context_(ctx),
        timestamp_(t),
        tags_(tags),
        metric_snapshots_(metric_snapshots) {
}

MetricsRecord::~MetricsRecord() {
}

string MetricsRecord::getContext() const {
    return this->context_;
}

time_t MetricsRecord::getTimestamp() const {
    return this->timestamp_;
}

MetricsRecord::TAG_VECTOR MetricsRecord::getTags() const {
    return this->tags_;
}

MetricsRecord::METRIC_SNAPSHOT_VEC MetricsRecord::getMetrics() const {
    return this->metric_snapshots_;
}


//////////////////////////////////////////////////////////////////////////////////////////
//
// class MetricsRecordBuilder:
//

MetricsRecordBuilder::MetricsRecordBuilder(time_t t, const string& name, const string& desc, const string& ctx):
        BasicItem(name, desc),
        timestamp_(t),
        context_(ctx) {

}

MetricsRecordBuilder::~MetricsRecordBuilder() {

}

void MetricsRecordBuilder::setContext(const string& ctx) {
    this->context_ = ctx;
}

void MetricsRecordBuilder::addTag(MetricTagPtr tag) {
    if (tag.get() == NULL) {
        BOOST_ASSERT_MSG(false, "NULL pointer encountered in MetricsRecordBuilder::addTag()!");
        return;
    }

    // check weather the tag exist or not
    bool already_exists = this->tags_.count(tag->getName()) > 0;
    if (already_exists) {
        METRICS_LOG_ERROR("Tag <%s> already exists in metrics record <%s>", tag->getName().c_str(), this->getName().c_str());
        BOOST_ASSERT(false);
    }
    else {
        this->tags_[tag->getName()] = tag;
    }
}

void MetricsRecordBuilder::addTag(const std::string& name, const std::string& desc, const std::string& value) {
    MetricTagPtr new_tag(new MetricTag(name, desc, value));
    this->addTag(new_tag);
}

void MetricsRecordBuilder::add(MetricSnapshotPtr metric) {
    if (metric.get() == NULL) {
        BOOST_ASSERT_MSG(false, "NULL pointer encountered in MetricsRecordBuilder::addCounter()!");
        return;
    }

    // check weather the metric exist or not
    bool already_exists = this->metrics_.count(metric->getName()) > 0;
    if (already_exists) {
        METRICS_LOG_ERROR("Metric <%s> already exists in metrics record <%s>", metric->getName().c_str(), this->getName().c_str());
        BOOST_ASSERT(false);
    }
    else {
        this->metrics_[metric->getName()] = metric;
    }
}

void MetricsRecordBuilder::addCounter(const BasicItemReadOnly& info, int val) {
    MetricSnapshotPtr new_counter(new MetricCounterInt(info, val));
    add(new_counter);
}

void MetricsRecordBuilder::addCounter(const BasicItemReadOnly& info, long val) {
    MetricSnapshotPtr new_counter(new MetricCounterLong(info, val));
    add(new_counter);
}

void MetricsRecordBuilder::addGauge(const BasicItemReadOnly& info, int val) {
    MetricSnapshotPtr new_gauge(new MetricGaugeInt(info, val));
    add(new_gauge);
}

void MetricsRecordBuilder::addGauge(const BasicItemReadOnly& info, long val) {
    MetricSnapshotPtr new_gauge(new MetricGaugeLong(info, val));
    add(new_gauge);
}

void MetricsRecordBuilder::addGauge(const BasicItemReadOnly& info, float val) {
    MetricSnapshotPtr new_gauge(new MetricGaugeFloat(info, val));
    add(new_gauge);
}
void MetricsRecordBuilder::addGauge(const BasicItemReadOnly& info, double val) {
    MetricSnapshotPtr new_gauge(new MetricGaugeDouble(info, val));
    add(new_gauge);
}

MetricsRecordPtr MetricsRecordBuilder::getRecord() {
    MetricsRecord::TAG_VECTOR tag_vec;
    {
        tag_vec.reserve(this->tags_.size());
        for (TAGS_MAP_T::const_iterator it = this->tags_.begin(); it != this->tags_.end(); it++) {
            tag_vec.push_back(it->second);
        }
    }

    MetricsRecord::METRIC_SNAPSHOT_VEC metric_snapshot_vec;
    {
        metric_snapshot_vec.reserve(this->metrics_.size());
        for (METRICS_MAP_T::const_iterator it = this->metrics_.begin(); it != this->metrics_.end(); it++) {
            metric_snapshot_vec.push_back(it->second);
        }
    }

    MetricsRecordPtr record(new MetricsRecord(this->getReadOnlyItem(), this->context_, this->timestamp_, tag_vec, metric_snapshot_vec));
    return record;
}

} /* namespace gmf */
