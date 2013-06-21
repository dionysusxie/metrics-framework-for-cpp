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
    MetricsRecordBuilder record_bulider(this->getName(), this->getDescription(), this->context_);

    // add some tags
    {
        record_bulider.addTag("name", "author_name", "Dio Xie");
        record_bulider.addTag("age", "author_age", "29");
    }

    return record_bulider.getRecord();
}

} /* namespace source */
} /* namespace gmf */
