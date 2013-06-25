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
        MetricsSource(name, "a metric source for testing", "test"),
        read_times_(BasicItemReadOnly("read_times"), 0),
        write_times_(BasicItemReadOnly("write_times"), 0) {
}

ConstMetricsRecordPtr Test::getMetrics() {
    MetricsRecordBuilder record_bulider(this->getName(), this->getDescription(), this->context_);

    // add some tags
    {
        record_bulider.addTag("name", "author_name", "Dio Xie");
        record_bulider.addTag("age", "author_age", "29");
    }

    // add metrics
    {
        this->read_times_.snapshot(record_bulider);
        this->write_times_.snapshot(record_bulider, true);
    }

    return record_bulider.getRecord();
}

void Test::incrReadTimes() {
    this->read_times_.incr();
}

void Test::incrWriteTimes() {
    this->write_times_.incr();
}

} /* namespace source */
} /* namespace gmf */
