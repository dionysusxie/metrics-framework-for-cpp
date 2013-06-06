/*
 * MetricsSource.h
 *
 *  Created on: Jun 4, 2013
 *      Author: xieliang
 */

#ifndef METRICSSOURCE_H_
#define METRICSSOURCE_H_

#include "MetricsRecord.h"

namespace gmf {
namespace source {

class MetricsSource {
public:
    MetricsSource();
    virtual ~MetricsSource();

public:
    virtual MetricsRecordPtr getMetrics() = 0;
};

class Test: public MetricsSource {
public:
    virtual MetricsRecordPtr getMetrics();
};

} /* namespace source */
} /* namespace gmf */

#endif /* METRICSSOURCE_H_ */
