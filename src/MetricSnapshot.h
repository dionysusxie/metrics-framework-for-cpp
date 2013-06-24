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

class MetricSnapshot;
typedef boost::shared_ptr<MetricSnapshot> MetricSnapshotPtr;
typedef boost::shared_ptr<const MetricSnapshot> MetricSnapshotCPtr;

class MetricSnapshot: public BasicItemReadOnly {
public:
    MetricSnapshot(const BasicItemReadOnly& info);
    virtual ~MetricSnapshot();
public:
    virtual MetricType getType() const = 0;
    virtual number::NumberPtr getValue() const = 0;
};


class MetricCounterInt: public MetricSnapshot {
public:
    MetricCounterInt(const BasicItemReadOnly& info, int val);
public:
    virtual MetricType getType() const;
    virtual number::NumberPtr getValue() const;
private:
    int value_;
};


class MetricCounterLong: public MetricSnapshot {
public:
    MetricCounterLong(const BasicItemReadOnly& info, long val);
public:
    virtual MetricType getType() const;
    virtual number::NumberPtr getValue() const;
private:
    long value_;
};

} /* namespace gmf */

#endif /* METRICSNAPSHOT_H_ */
