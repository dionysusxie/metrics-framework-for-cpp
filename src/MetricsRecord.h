/*
 * MetricsRecord.h
 *
 *  Created on: May 27, 2013
 *      Author: xieliang
 */

#ifndef METRICSRECORD_H_
#define METRICSRECORD_H_

#include <string>
#include <map>
#include <vector>
#include "gmf_common.h"
#include "BasicItem.h"
#include "MetricTag.h"
#include "MetricSnapshot.h"

namespace gmf {

class MetricsRecord;
typedef boost::shared_ptr<MetricsRecord> MetricsRecordPtr;
typedef boost::shared_ptr<const MetricsRecord> ConstMetricsRecordPtr;

// An immutable snapshot of metrics with a timestamp
// Thread safe as its public methods are all const.
class MetricsRecord: public BasicItemReadOnly {
public:
    typedef std::vector<MetricTagCPtr> TAG_VECTOR;
    typedef std::vector<MetricSnapshotCPtr> METRIC_SNAPSHOT_VEC;
public:
    MetricsRecord(const BasicItemReadOnly& info, const std::string& ctx, time_t t,
            const TAG_VECTOR& tags, const METRIC_SNAPSHOT_VEC& metric_snapshots);
    virtual ~MetricsRecord();

public:
    std::string getContext() const;
    time_t getTimestamp() const;
    TAG_VECTOR getTags() const;
    METRIC_SNAPSHOT_VEC getMetrics() const;

private:
    std::string context_;
    time_t timestamp_;
    TAG_VECTOR tags_;
    METRIC_SNAPSHOT_VEC metric_snapshots_;
};


// Not thread safe!
class MetricsRecordBuilder: public BasicItem {
public:
    typedef std::map<std::string, MetricTagPtr> TAGS_MAP_T;
    typedef std::map<std::string, MetricSnapshotPtr> METRICS_MAP_T;
public:
    MetricsRecordBuilder(const std::string& name="", const std::string& desc="", const std::string& ctx="");
    ~MetricsRecordBuilder();
public:
    void setContext(const std::string& ctx);

    void addTag(MetricTagPtr tag);
    void addTag(const std::string& name, const std::string& desc, const std::string& value);

    void add(MetricSnapshotPtr metric);
    void addCounter(const BasicItemReadOnly& info, int val);
    void addCounter(const BasicItemReadOnly& info, long val);

    MetricsRecordPtr getRecord();
private:
    std::string context_;
    TAGS_MAP_T tags_;
    METRICS_MAP_T metrics_;
};

} /* namespace gmf */
#endif /* METRICSRECORD_H_ */
