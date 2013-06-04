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

// An immutable snapshot of metrics with a timestamp
class MetricsRecord: public BasicItem {
public:
    MetricsRecord(const std::string& name, const std::string& desc);
    virtual ~MetricsRecord();

public:
    time_t getTimestamp() const;
    std::string getContext() const;
    std::map<std::string, MetricTag> getTags() const;

};

} /* namespace gmf */
#endif /* METRICSRECORD_H_ */
