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

MetricsRecord::MetricsRecord(const string& name, const string& desc, const string& ctx,
        time_t t, const TAG_VECTOR& tags):
        BasicItemReadOnly(name, desc),
        context_(ctx),
        timestamp_(t),
        tags_(tags) {
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


//////////////////////////////////////////////////////////////////////////////////////////
//
// class MetricsRecordBuilder:
//

MetricsRecordBuilder::MetricsRecordBuilder(const string& name, const string& desc, const string& ctx):
        BasicItem(name, desc),
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

MetricsRecordPtr MetricsRecordBuilder::getRecord() const {
    const time_t time_now = time(NULL);

    MetricsRecord::TAG_VECTOR tag_vec;
    {
        tag_vec.reserve(this->tags_.size());
        for (TAGS_MAP_T::const_iterator it = this->tags_.begin(); it != this->tags_.end(); it++) {
            tag_vec.push_back(it->second);
        }
    }

    MetricsRecordPtr record(new MetricsRecord(this->getName(), this->getDescription(),
            this->context_, time_now, tag_vec));
    return record;
}

} /* namespace gmf */
