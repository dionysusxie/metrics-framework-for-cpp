/*
 * MetricsSource.h
 *
 *  Created on: Jun 4, 2013
 *      Author: xieliang
 */

#ifndef METRICSSOURCE_H_
#define METRICSSOURCE_H_

#include "MetricsRecord.h"
#include "MutableMetric.h"
#include "gmf_common.h"

namespace gmf {
namespace source {

class MetricsSource;
typedef boost::shared_ptr<MetricsSource> MetricsSourcePtr;


class MetricsSource: public BasicItem {
public:
    MetricsSource(const std::string& name, const std::string& desc, const std::string& ctx);
    virtual ~MetricsSource();

public:
    virtual ConstMetricsRecordPtr getMetrics() = 0;
protected:
    const std::string context_;
};

class Test: public MetricsSource {
public:
    Test(const std::string& name = "test");
    virtual ConstMetricsRecordPtr getMetrics();
private:
    MutableCounterInt read_times_;
};

} /* namespace source */
} /* namespace gmf */

#endif /* METRICSSOURCE_H_ */
