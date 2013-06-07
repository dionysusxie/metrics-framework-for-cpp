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
    std::string getType() const;
    void config(StoreConf_SPtr conf);
    void putMetrics(std::vector<MetricsRecordPtr> records);

protected:
    virtual void consumeRecords(std::queue<MetricsRecordPtr>) = 0;

private:
    const std::string type_;

    // Queue of metrics records;
    // New metrics records would be lost if the queue is full.
    std::queue<MetricsRecordPtr> record_queue_;
    size_t max_queue_size_;
    boost::mutex queue_lock_;

    // Thread to consume metrics records
    boost::shared_ptr<boost::thread> sink_thread_;
};


class SinkToConsole: public MetricsSink {
public:
    static const std::string TYPE_TXT;
public:
    SinkToConsole();
protected:
    virtual void consumeRecords(std::queue<MetricsRecordPtr>);
};

} /* namespace sink */
} /* namespace gmf */

#endif /* METRICSSINK_H_ */
