/*
 * AbstractMetric.cpp
 *
 *  Created on: May 30, 2013
 *      Author: xieliang
 */

#include "MetricSnapshot.h"

namespace gmf {

MetricSnapshot::MetricSnapshot(MetricType type, const std::string& name, const std::string& desc):
        BasicItemReadOnly(name, desc),
        type_(type) {
}

MetricSnapshot::~MetricSnapshot() {
}

MetricType MetricSnapshot::getType() const {
    return this->type_;
}

number::NumberCPtr MetricSnapshot::getValue() const {
    return this->value_;
}

} /* namespace gmf */
