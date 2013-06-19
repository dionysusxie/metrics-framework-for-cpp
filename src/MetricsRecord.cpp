/*
 * MetricsRecord.cpp
 *
 *  Created on: May 27, 2013
 *      Author: xieliang
 */

#include "MetricsRecord.h"

namespace gmf {

MetricsRecord::MetricsRecord(const std::string& name, const std::string& desc,
        const std::string& ctx):
        BasicItemReadOnly(name, desc),
        context_(ctx),
        timestamp_(time(NULL)) {
}

MetricsRecord::~MetricsRecord() {
}

time_t MetricsRecord::getTimestamp() const {
    return this->timestamp_;
}

std::string MetricsRecord::getContext() const {
    return this->context_;
}

MetricsRecord::TAGS_MAP_T MetricsRecord::getTags() const {
    return this->tags_;
}

bool MetricsRecord::addTag(ConstMetricTagPtr tag) {
    if (tag.get() == NULL) {
        METRICS_LOG_ERROR("NULL pointer encountered in MetricsRecord::addTag()!");
        return false;
    }

    // check weather the tag exist or not
    bool already_exists = this->tags_.count(tag->getName()) > 0;
    if (already_exists) {
        METRICS_LOG_ERROR("Tag <%s> already exists in metrics record <%s>",
                tag->getName().c_str(), this->getName().c_str());
        return false;
    }

    this->tags_[tag->getName()] = tag;
    return true;
}

} /* namespace gmf */
