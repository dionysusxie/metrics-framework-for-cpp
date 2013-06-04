/*
 * AbstractMetric.cpp
 *
 *  Created on: May 30, 2013
 *      Author: xieliang
 */

#include "AbstractMetric.h"

namespace gmf {

AbstractMetric::AbstractMetric(MetricType type, const std::string& name, const std::string& desc):
    BasicItem(name, desc),
    type_(type) {

}

AbstractMetric::~AbstractMetric() {
    // TODO Auto-generated destructor stub
}

MetricType AbstractMetric::getType() const {
    return this->type_;
}

} /* namespace gmf */
