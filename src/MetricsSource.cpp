/*
 * MetricsSource.cpp
 *
 *  Created on: Jun 4, 2013
 *      Author: xieliang
 */

#include "MetricsSource.h"

namespace gmf {
namespace source {

MetricsSource::MetricsSource(const std::string& name, const std::string& desc):
    BasicItem(name, desc) {
    // TODO Auto-generated constructor stub

}

MetricsSource::~MetricsSource() {
    // TODO Auto-generated destructor stub
}


//////////////////////////////////////////////////////////////////////////////////////////
//
// class Test:
//

Test::Test():
        MetricsSource("test-source", "a metric source for testing") {
}

ConstMetricsRecordPtr Test::getMetrics() {
    ConstMetricsRecordPtr record(new MetricsRecord("test", "just for testing", "test"));
    return record;
}

} /* namespace source */
} /* namespace gmf */
