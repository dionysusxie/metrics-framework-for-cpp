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

extern std::ostream& operator << (std::ostream&, const MetricSnapshot&);


class MetricSnapshot: public BasicItemReadOnly {
public:
    MetricSnapshot(const BasicItemReadOnly& info);
    virtual ~MetricSnapshot();
public:
    virtual MetricType getType() const = 0;
    virtual number::NumberPtr getValue() const = 0;
};


//
// Counter
//

template <class T>
class MetricCounter: public MetricSnapshot {
public:
    MetricCounter(const BasicItemReadOnly& info, T val):
        MetricSnapshot(info),
        value_(val) {
    }
public:
    virtual MetricType getType() const {
        return gmf::COUNTER;
    }
    virtual number::NumberPtr getValue() const {
        return number::Number::newNumber(value_);
    }
    T getRawValue() const {
        return value_;
    }
private:
    T value_;
};

typedef MetricCounter<int> MetricCounterInt;
typedef MetricCounter<long> MetricCounterLong;


//
// Gauge
//

template <class T>
class MetricGauge: public MetricSnapshot {
public:
    MetricGauge(const BasicItemReadOnly& info, T val):
        MetricSnapshot(info),
        value_(val) {
    }
public:
    virtual MetricType getType() const {
        return gmf::GAUGE;
    }
    virtual number::NumberPtr getValue() const {
        return number::Number::newNumber(value_);
    }
    T getRawValue() const {
        return value_;
    }
private:
    T value_;
};

typedef MetricGauge<int> MetricGaugeInt;
typedef MetricGauge<long> MetricGaugeLong;
typedef MetricGauge<float> MetricGaugeFloat;
typedef MetricGauge<double> MetricGaugeDouble;

} /* namespace gmf */

#endif /* METRICSNAPSHOT_H_ */
