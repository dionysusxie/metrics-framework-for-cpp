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
public:
    void config(const std::string& conf_file);
    void config(StoreConf_SPtr conf);
    void registerSource(source::MetricsSourcePtr);
    void start();
    void stop();
    void threadFunc();
private:
    MetricsSystem();
    bool registerSink(sink::MetricsSinkPtr sink);
private:
    static boost::shared_ptr<MetricsSystem> s_pSingleton;
private:
    // key: name of metrics source
    typedef std::map<std::string, source::MetricsSourcePtr> SOURCE_CONTAINER_T;
    // key: name of metrics sink
    typedef std::map<std::string, sink::MetricsSinkPtr> SINK_CONTAINER_T;
private:
    // All public methods except threadFunc() have to get this lock first!
    boost::recursive_timed_mutex common_mutex_;

    SOURCE_CONTAINER_T sources_;
    SINK_CONTAINER_T sinks_;

    // Thread to collect metrics from all registered sources, then push them to
    // registered sinks.
    // NULL ptr means no thead created.
    boost::shared_ptr<boost::thread> metrics_collecting_thread_;
    unsigned long metrics_collecting_interval_;

    // commands for the thread
    enum EnumCommand {
        CMD_STOP = 0,
        CMD_MAX
    };
    std::queue<EnumCommand> thread_cmds_;
    boost::mutex thread_cmds_mutex_;
};

} /* namespace gmf */
#endif /* METRICSSYSTEM_H_ */
