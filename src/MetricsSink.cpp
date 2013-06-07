/*
 * MetricsSink.cpp
 *
 *  Created on: Jun 4, 2013
 *      Author: xieliang
 */

#include <iostream>
#include "MetricsSink.h"


using namespace std;
using namespace boost;


namespace gmf {
namespace sink {

/* static */ MetricsSinkPtr MetricsSink::createSink(StoreConf_SPtr conf) {
    string type;
    conf->getString("type", type);

    MetricsSinkPtr sink;
    if (SinkToConsole::TYPE_TXT == type) {
        sink.reset(new SinkToConsole());
    }
    else {
        const string fail_msg = "Invalid sink type: " + type;
        METRICS_LOG_ERROR(fail_msg);
        BOOST_ASSERT_MSG(false, fail_msg.c_str());
    }

    sink->config(conf);

    return sink;
}

MetricsSink::MetricsSink(const std::string& type):
    type_(type) {
    // TODO Auto-generated constructor stub

}

MetricsSink::~MetricsSink() {
    // TODO Auto-generated destructor stub
}

std::string MetricsSink::getType() const {
    return this->type_;
}

void MetricsSink::config(StoreConf_SPtr conf) {

}


//////////////////////////////////////////////////////////////////////////////////////////
//
// class SinkToConsole:
//

const string SinkToConsole::TYPE_TXT = "console";

SinkToConsole::SinkToConsole():
        MetricsSink(TYPE_TXT) {
}

// Write records to std.
void SinkToConsole::consumeRecords(std::queue<MetricsRecordPtr> records) {
    while (!records.empty()) {
        MetricsRecordPtr r = records.front();

        string out_line;
        {
            out_line = r->getTimestamp() + "  " + r->getName() + "." + r->getContext() +
                    ", " + r->getDescription();
        }
        cout << out_line << endl;

        records.pop();
    }
}

} /* namespace sink */
} /* namespace gmf */
