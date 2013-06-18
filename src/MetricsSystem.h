/*
 * MetricsSystem.h
 *
 *  Created on: Jun 4, 2013
 *      Author: xieliang
 */

#ifndef METRICSSYSTEM_H_
#define METRICSSYSTEM_H_

#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
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
    void start();
    void stop();

private:
    MetricsSystem();

    bool registerSource(source::MetricsSourcePtr);
    bool registerSink(sink::MetricsSinkPtr sink);
    void registerYourSources();

private:
    static boost::shared_ptr<MetricsSystem> s_pSingleton;
private:
    // key: name of metrics source
    typedef std::map<std::string, source::MetricsSourcePtr> SOURCE_CONTAINER_T;
    // key: name of metrics sink
    typedef std::map<std::string, sink::MetricsSinkPtr> SINK_CONTAINER_T;
private:
    // All public methods have to get this lock first!
    boost::recursive_timed_mutex common_mutex_;

    SOURCE_CONTAINER_T sources_;
    SINK_CONTAINER_T sinks_;
};

} /* namespace gmf */
#endif /* METRICSSYSTEM_H_ */
