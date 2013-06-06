/*
 * MetricsSource.cpp
 *
 *  Created on: Jun 4, 2013
 *      Author: xieliang
 */

#include "MetricsSource.h"

namespace gmf {
namespace source {

MetricsSource::MetricsSource() {
    // TODO Auto-generated constructor stub

}

MetricsSource::~MetricsSource() {
    // TODO Auto-generated destructor stub
}


MetricsRecordPtr Test::getMetrics() {
    return MetricsRecordPtr(new MetricsRecord("test", "just for testing"));
}

} /* namespace source */
} /* namespace gmf */
