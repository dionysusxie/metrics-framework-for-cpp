/*
 * AbstractMetric.cpp
 *
 *  Created on: May 30, 2013
 *      Author: xieliang
 */

#include "MetricSnapshot.h"

namespace gmf {

std::ostream& operator << (std::ostream& os, const MetricSnapshot& m) {
    os << "(" << m.getName() << "," << m.getType() << "," << (*m.getValue()) << ")";
    return os;
}


//////////////////////////////////////////////////////////////////////////////////////////
//
// class MetricSnapshot:
//

MetricSnapshot::MetricSnapshot(const BasicItemReadOnly& info):
        BasicItemReadOnly(info) {
}

MetricSnapshot::~MetricSnapshot() {
}

} /* namespace gmf */
