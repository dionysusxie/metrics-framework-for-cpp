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
class Test;

typedef boost::shared_ptr<MetricsSource> MetricsSourcePtr;
typedef boost::shared_ptr<Test> TestPtr;

class MetricsSource: public BasicItem {
public:
    MetricsSource(const std::string& name, const std::string& desc, const std::string& ctx);
    virtual ~MetricsSource();

public:
    virtual ConstMetricsRecordPtr getMetrics(time_t timestamp) = 0;
protected:
    const std::string context_;
};

class Test: public MetricsSource {
public:
    Test(const std::string& name = "test");
public:
    virtual ConstMetricsRecordPtr getMetrics(time_t timestamp);
    void updateMetrics();
private:
    MutableCounterInt read_times_;
    MutableCounterLong write_times_;

    MutableGaugeInt weight_;

    MutableGaugeFloat height_;
    MutableGaugeDouble height2_;
};

} /* namespace source */
} /* namespace gmf */

#endif /* METRICSSOURCE_H_ */
