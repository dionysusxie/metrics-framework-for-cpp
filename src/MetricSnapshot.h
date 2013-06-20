/*
 * MetricSnapshot.h
 *
 *  Created on: May 30, 2013
 *      Author: xieliang
 */

#ifndef METRICSNAPSHOT_H_
#define METRICSNAPSHOT_H_

#include <string>
#include "BasicItem.h"
#include "gmf_common.h"
#include "Number.h"


namespace gmf {

class MetricSnapshot: public BasicItemReadOnly {
public:
    MetricSnapshot(const std::string& name="", const std::string& desc="");
    virtual ~MetricSnapshot();
public:
    virtual MetricType getType() const = 0;
    virtual number::Number_CRef getValue() const = 0;
};


class MetricCounterInt: public MetricSnapshot {
public:
    MetricCounterInt(int val, const std::string& name="", const std::string& desc="");
public:
    virtual MetricType getType() const;
    virtual number::Number_CRef getValue() const;
private:
    number::Int value_;
};


class MetricCounterLong: public MetricSnapshot {
public:
    MetricCounterLong(long val, const std::string& name="", const std::string& desc="");
public:
    virtual MetricType getType() const;
    virtual number::Number_CRef getValue() const;
private:
    number::Long value_;
};

} /* namespace gmf */

#endif /* METRICSNAPSHOT_H_ */
