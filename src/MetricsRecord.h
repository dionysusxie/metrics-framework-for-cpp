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

// An immutable snapshot of metrics with a timestamp
class MetricsRecord: public BasicItemReadOnly {
public:
    MetricsRecord(const std::string& name, const std::string& desc,
            const std::string& ctx);
    virtual ~MetricsRecord();

public:
    time_t getTimestamp() const;
    std::string getContext() const;
    std::map<std::string, MetricTag> getTags() const;

private:
    const std::string context_;
    const time_t timestamp_;
    std::map<std::string, MetricTag> tags_;
};

} /* namespace gmf */
#endif /* METRICSRECORD_H_ */
