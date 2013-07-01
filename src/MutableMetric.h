/*
 * MutableMetric.h
 *
 *  Created on: Jun 20, 2013
 *      Author: xieliang
 */

#ifndef MUTABLEMETRIC_H_
#define MUTABLEMETRIC_H_

#include <boost/thread.hpp>
#include "MetricsRecord.h"
#include "Number.h"


namespace gmf {

class MutableMetric: public BasicItem {
public:
    MutableMetric(const BasicItemReadOnly& info);
    virtual ~MutableMetric();
public:
    void snapshot(MetricsRecordBuilder& builder, bool all = false);
    bool changed();
protected:
    void setChanged();
    void clearChanged();
    virtual void snapshotImpl(MetricsRecordBuilder& builder) = 0;
private:
    bool changed_;
    boost::shared_mutex changed_mutex_;
};


//
// Counter
//

// Thread safe!
template<class T>
class MutableCounter: public MutableMetric {
public:
    typedef T VALUE_TYPE;
public:
    MutableCounter(const BasicItemReadOnly& info, VALUE_TYPE init_value = 0);
public:
    VALUE_TYPE value();
    void incr(VALUE_TYPE delta = 1);
protected:
    virtual void snapshotImpl(MetricsRecordBuilder& builder);
private:
    VALUE_TYPE value_;
    boost::shared_mutex value_mutex_;
};

typedef MutableCounter<int> MutableCounterInt;
typedef MutableCounter<long> MutableCounterLong;


//
// Gauge
//

// Thread safe!
template<class T>
class MutableGauge: public MutableMetric {
public:
    typedef T VALUE_TYPE;
public:
    MutableGauge(const BasicItemReadOnly& info, VALUE_TYPE init_value = 0);
public:
    VALUE_TYPE value();
    void incr(VALUE_TYPE delta = 1);
    void decr(VALUE_TYPE delta = 1);
    void set(VALUE_TYPE new_value);
protected:
    virtual void snapshotImpl(MetricsRecordBuilder& builder);
private:
    VALUE_TYPE value_;
    boost::shared_mutex value_mutex_;
};

typedef MutableGauge<int> MutableGaugeInt;
typedef MutableGauge<long> MutableGaugeLong;
typedef MutableGauge<float> MutableGaugeFloat;
typedef MutableGauge<double> MutableGaugeDouble;

#include "MutableMetric.inl"
} /* namespace gmf */
#endif /* MUTABLEMETRIC_H_ */
