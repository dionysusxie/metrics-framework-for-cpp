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

class MetricGauge: public MetricSnapshot {
public:
    MetricGauge(const BasicItemReadOnly& info);
public:
    virtual MetricType getType() const;
};

class MetricGaugeInt: public MetricGauge {
public:
    MetricGaugeInt(const BasicItemReadOnly& info, int val);
public:
    virtual number::NumberPtr getValue() const;
private:
    int value_;
};

class MetricGaugeLong: public MetricGauge {
public:
    MetricGaugeLong(const BasicItemReadOnly& info, long val);
public:
    virtual number::NumberPtr getValue() const;
private:
    long value_;
};

class MetricGaugeFloat: public MetricGauge {
public:
    MetricGaugeFloat(const BasicItemReadOnly& info, float val);
public:
    virtual number::NumberPtr getValue() const;
private:
    float value_;
};

class MetricGaugeDouble: public MetricGauge {
public:
    MetricGaugeDouble(const BasicItemReadOnly& info, double val);
public:
    virtual number::NumberPtr getValue() const;
private:
    double value_;
};

} /* namespace gmf */

#endif /* METRICSNAPSHOT_H_ */
