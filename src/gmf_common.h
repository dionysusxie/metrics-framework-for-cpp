/*
 * gmf_common.h
 *
 *  Created on: May 29, 2013
 *      Author: xieliang
 */

#ifndef GMF_COMMON_H_
#define GMF_COMMON_H_

#include <string>
#include <stddef.h>
#include <allyes-log.h>
#include <boost/shared_ptr.hpp>


#define METRICS_LOG_DEBUG(format_string, ...) LOG_DEBUG_CTX(gmf::METRICS_LOG_CONTEXT, format_string, ##__VA_ARGS__)
#define METRICS_LOG_INFO(format_string, ...) LOG_INFO_CTX(gmf::METRICS_LOG_CONTEXT, format_string, ##__VA_ARGS__)
#define METRICS_LOG_WARNING(format_string, ...) LOG_WARNING_CTX(gmf::METRICS_LOG_CONTEXT, format_string, ##__VA_ARGS__)
#define METRICS_LOG_ERROR(format_string, ...) LOG_ERROR_CTX(gmf::METRICS_LOG_CONTEXT, format_string, ##__VA_ARGS__)


namespace gmf {

enum MetricType {
    COUNTER = 0, // A monotonically increasing metric that can be used to calculate throughput
    GAUGE,       // An arbitrary varying metric
    MAX
};

extern std::string toString(enum MetricType);
extern std::ostream& operator << (std::ostream&, MetricType);

extern const std::string METRICS_LOG_CONTEXT;
extern const std::string TXT_SINK;
}

#endif /* GMF_COMMON_H_ */
