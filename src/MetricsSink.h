/*
 * MetricsSink.h
 *
 *  Created on: Jun 4, 2013
 *      Author: xieliang
 */

#ifndef METRICSSINK_H_
#define METRICSSINK_H_

#include <vector>
#include <queue>
#include <boost/thread.hpp>
#include "MetricsRecord.h"
#include "conf.h"


namespace gmf {
namespace sink {

class MetricsSink;
typedef boost::shared_ptr<MetricsSink> MetricsSinkPtr;


class MetricsSink: public BasicItem {
public:
    static MetricsSinkPtr createSink(StoreConf_SPtr conf);
public:
    MetricsSink(const std::string& type);
    virtual ~MetricsSink();
public:
    std::string getType();

    void config(StoreConf_SPtr conf);
    void open();
    void close();
    void putMetrics(const std::vector<ConstMetricsRecordPtr>& records);

    void threadFunc();

public:
    typedef std::queue<ConstMetricsRecordPtr> RECORDS_QUEUE;
    typedef boost::shared_ptr<RECORDS_QUEUE> RECORDS_QUEUE_PTR;

protected:
    virtual void configImpl(StoreConf_SPtr conf) = 0;
    virtual void openImpl() = 0;
    virtual void closeImpl() = 0;
    virtual void consumeRecords(RECORDS_QUEUE_PTR) = 0;

private:
    // All public method except threadFunc() have to get this lock first!
    boost::recursive_timed_mutex public_mutex_;

    const std::string type_;
    bool configed_;

    // Queue of metrics records;
    // New metrics records would be lost if the queue is full.
    RECORDS_QUEUE_PTR record_queue_;
    unsigned long max_queue_size_;
    boost::mutex queue_lock_; // All operations relative to the queue must get this lock first!

    // Thread to consume metrics records
    // NULL ptr means no thead created.
    boost::shared_ptr<boost::thread> sink_thread_;

    // commands for the thread
    enum EnumCommand {
        CMD_STOP = 0,
        CMD_MAX
    };
    std::queue<EnumCommand> thread_cmds_;
    boost::mutex thread_cmds_mutex_;

    // has work?
    bool has_work_;
    boost::mutex has_work_mutex_;
    boost::condition_variable_any has_work_cond_;
};


class SinkToConsole: public MetricsSink {
public:
    static const std::string TYPE_TXT;
public:
    SinkToConsole();
protected:
    virtual void configImpl(StoreConf_SPtr conf);
    virtual void openImpl();
    virtual void closeImpl();
    virtual void consumeRecords(RECORDS_QUEUE_PTR);
};

} /* namespace sink */
} /* namespace gmf */

#endif /* METRICSSINK_H_ */
