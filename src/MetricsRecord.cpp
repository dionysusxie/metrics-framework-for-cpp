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
    BasicItem(name, desc),
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

std::map<std::string, MetricTag> MetricsRecord::getTags() const {
    return this->tags_;
}

} /* namespace gmf */
