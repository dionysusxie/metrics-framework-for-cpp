/*
 * AbstractMetric.cpp
 *
 *  Created on: May 30, 2013
 *      Author: xieliang
 */

#include "MetricSnapshot.h"

namespace gmf {

MetricSnapshot::MetricSnapshot(MetricType type, const std::string& name, const std::string& desc):
    BasicItem(name, desc),
    type_(type) {

}

MetricSnapshot::~MetricSnapshot() {
    // TODO Auto-generated destructor stub
}

MetricType MetricSnapshot::getType() const {
    return this->type_;
}

} /* namespace gmf */
