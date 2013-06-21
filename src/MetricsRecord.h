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


namespace gmf {

class MetricsRecord;
typedef boost::shared_ptr<MetricsRecord> MetricsRecordPtr;
typedef boost::shared_ptr<const MetricsRecord> ConstMetricsRecordPtr;

// An immutable snapshot of metrics with a timestamp
class MetricsRecord: public BasicItemReadOnly {
public:
    typedef std::vector<MetricTagCPtr> TAG_VECTOR;
public:
    MetricsRecord(const std::string& name, const std::string& desc,
            const std::string& ctx, time_t t, const TAG_VECTOR& tags);
    virtual ~MetricsRecord();

public:
    std::string getContext() const;
    time_t getTimestamp() const;
    TAG_VECTOR getTags() const;

private:
    std::string context_;
    time_t timestamp_;
    TAG_VECTOR tags_;
};


class MetricsRecordBuilder: public BasicItem {
public:
    typedef std::map<std::string, MetricTagPtr> TAGS_MAP_T;
public:
    MetricsRecordBuilder(const std::string& name="", const std::string& desc="", const std::string& ctx="");
    ~MetricsRecordBuilder();
public:
    void setContext(const std::string& ctx);
    void addTag(MetricTagPtr tag);
    void addTag(const std::string& name, const std::string& desc, const std::string& value);
    MetricsRecordPtr getRecord() const;
private:
    std::string context_;
    TAGS_MAP_T tags_;
};

} /* namespace gmf */
#endif /* METRICSRECORD_H_ */
