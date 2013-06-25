/*
 * gmf_common.cpp
 *
 *  Created on: Jun 5, 2013
 *      Author: xieliang
 */

#include "gmf_common.h"

using namespace std;

namespace gmf {
string toString(enum MetricType mt) {
    static const string s_type_strs[MAX] = {
            "COUNTER",
            "GAUGE",
    };

    if (mt < MAX) {
        return s_type_strs[mt];
    }
    else {
        BOOST_ASSERT_MSG(false, "enum MetricType out of range!");
        return "";
    }
}

ostream& operator << (ostream& os, MetricType t) {
    os << toString(t);
    return os;
}

const std::string METRICS_LOG_CONTEXT = "metrics";
const std::string TXT_SINK = "sink";
}
