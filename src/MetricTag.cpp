/*
 * MetricTag.cpp
 *
 *  Created on: Jun 3, 2013
 *      Author: xieliang
 */

#include "MetricTag.h"

namespace gmf {

MetricTag::MetricTag(const std::string& name, const std::string& desc, const std::string& value):
    BasicItem(name, desc),
    value_(value) {
    // TODO Auto-generated constructor stub

}

MetricTag::~MetricTag() {
    // TODO Auto-generated destructor stub
}

std::string MetricTag::getValue() const {
    return this->value_;
}

} /* namespace gmf */
