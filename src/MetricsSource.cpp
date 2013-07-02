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
        write_times_(BasicItemReadOnly("write_times"), 0),
        weight_(BasicItemReadOnly("weight", "my weight in KG"), 65),
        height_(BasicItemReadOnly("height", "my height in CM"), 170),
        height2_(BasicItemReadOnly("height2", "my height in CM"), 170) {
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

        weight_.snapshot(record_bulider);

        height_.snapshot(record_bulider);
        height2_.snapshot(record_bulider);
    }

    return record_bulider.getRecord();
}

void Test::updateMetrics() {
    this->read_times_.incr(1);
    this->write_times_.incr(2);

    this->weight_.incr(2);

    this->height_.incr();
    this->height2_.decr();
}

} /* namespace source */
} /* namespace gmf */
