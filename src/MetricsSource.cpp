/*
 * MetricsSource.cpp
 *
 *  Created on: Jun 4, 2013
 *      Author: xieliang
 */

#include "MetricsSource.h"

using namespace std;
using namespace boost;


namespace gmf {
namespace source {

MetricsSource::MetricsSource(const string& name, const string& desc, const string& ctx):
    BasicItem(name, desc),
    context_(ctx) {
}

MetricsSource::~MetricsSource() {
}


//////////////////////////////////////////////////////////////////////////////////////////
//
// class Test:
//

Test::Test():
        MetricsSource("test-source", "a metric source for testing", "test") {
}

ConstMetricsRecordPtr Test::getMetrics() {
    MetricsRecordPtr record(new MetricsRecord("test", this->getDescription(), this->context_));
    record->addTag(MetricTag("name", "author_name", "Dio Xie"));
    record->addTag(MetricTag("age", "author_age", "29"));

    return record;
}

} /* namespace source */
} /* namespace gmf */
