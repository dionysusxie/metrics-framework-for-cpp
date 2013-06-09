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


class MetricsSink {
public:
    static MetricsSinkPtr createSink(StoreConf_SPtr conf);
public:
    MetricsSink(const std::string& type);
    virtual ~MetricsSink();
public:
    std::string getType();
    std::string getName();

    void config(StoreConf_SPtr conf);
    void close();
    void putMetrics(std::vector<MetricsRecordPtr> records);

    void threadFunc();

protected:
    virtual void configImpl(StoreConf_SPtr conf) = 0;
    virtual void closeImpl() = 0;
    virtual void consumeRecords(std::queue<MetricsRecordPtr>) = 0;

private:
    // All public method except threadFunc() have to get this lock first!
    boost::recursive_timed_mutex public_mutex_;

    const std::string type_;
    std::string name_;

    // Queue of metrics records;
    // New metrics records would be lost if the queue is full.
    std::queue<MetricsRecordPtr> record_queue_;
    unsigned long max_queue_size_;
    boost::mutex queue_lock_; // All operations relative to the queue must get this lock first!

    // Thread to consume metrics records
    // NULL ptr means no thead created.
    boost::shared_ptr<boost::thread> sink_thread_;

};


class SinkToConsole: public MetricsSink {
public:
    static const std::string TYPE_TXT;
public:
    SinkToConsole();
protected:
    virtual void configImpl(StoreConf_SPtr conf);
    virtual void closeImpl();
    virtual void consumeRecords(std::queue<MetricsRecordPtr>);
};

} /* namespace sink */
} /* namespace gmf */

#endif /* METRICSSINK_H_ */
