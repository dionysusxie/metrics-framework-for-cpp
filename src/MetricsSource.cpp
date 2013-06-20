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

Test::Test(const std::string& name):
        MetricsSource(name, "a metric source for testing", "test") {
}

ConstMetricsRecordPtr Test::getMetrics() {
    MetricsRecordPtr record(new MetricsRecord(this->getName(), this->getDescription(), this->context_));

    // add some tags
    {
        ConstMetricTagPtr tag1(new MetricTag("name", "author_name", "Dio Xie"));
        ConstMetricTagPtr tag2(new MetricTag("age", "author_age", "29"));
        record->addTag(tag1);
        record->addTag(tag2);
    }

    return record;
}

} /* namespace source */
} /* namespace gmf */
