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

MetricsSink::MetricsSink() {
    // TODO Auto-generated constructor stub

}

MetricsSink::~MetricsSink() {
    // TODO Auto-generated destructor stub
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
