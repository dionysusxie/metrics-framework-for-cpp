/*
 * MetricsSource.h
 *
 *  Created on: Jun 4, 2013
 *      Author: xieliang
 */

#ifndef METRICSSOURCE_H_
#define METRICSSOURCE_H_

#include "MetricsRecord.h"
#include "gmf_common.h"

namespace gmf {
namespace source {

class MetricsSource;
typedef boost::shared_ptr<MetricsSource> MetricsSourcePtr;


class MetricsSource: public BasicItem {
public:
    MetricsSource(const std::string& name, const std::string& desc);
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
