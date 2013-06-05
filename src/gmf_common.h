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


namespace gmf {

enum MetricType {
    COUNTER = 0, // A monotonically increasing metric that can be used to calculate throughput
    GAUGE,       // An arbitrary varying metric
    MAX
};

}

#endif /* GMF_COMMON_H_ */
