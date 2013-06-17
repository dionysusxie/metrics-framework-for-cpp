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
    typedef std::map<std::string, MetricTag> TAGS_MAP_T;
public:
    MetricsRecord(const std::string& name, const std::string& desc,
            const std::string& ctx);
    virtual ~MetricsRecord();

public:
    time_t getTimestamp() const;
    std::string getContext() const;
    TAGS_MAP_T getTags() const;

private:
    const std::string context_;
    const time_t timestamp_;
    TAGS_MAP_T tags_;
};

} /* namespace gmf */
#endif /* METRICSRECORD_H_ */
