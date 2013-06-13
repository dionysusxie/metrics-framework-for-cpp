/*
 * MetricsSystem.h
 *
 *  Created on: Jun 4, 2013
 *      Author: xieliang
 */

#ifndef METRICSSYSTEM_H_
#define METRICSSYSTEM_H_

#include <boost/shared_ptr.hpp>
#include <map>
#include "gmf_common.h"
#include "MetricsSource.h"
#include "MetricsSink.h"


namespace gmf {

class MetricsSystem {
public:
    static boost::shared_ptr<MetricsSystem> getSingleton();

public:
    virtual ~MetricsSystem();

    bool config(StoreConf_SPtr conf);
    bool registerSource(source::MetricsSourcePtr);
    bool registerSink(sink::MetricsSinkPtr sink);
    void start();
    void stop();

private:
    MetricsSystem();

private:
    static boost::shared_ptr<MetricsSystem> s_pSingleton;
private:
    // key: name of metrics source
    std::map<std::string, source::MetricsSourcePtr> sources_;

    // key: name of metrics sink
    std::map<std::string, sink::MetricsSinkPtr> sinks_;
};

} /* namespace gmf */
#endif /* METRICSSYSTEM_H_ */
