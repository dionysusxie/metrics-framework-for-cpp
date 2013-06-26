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

class MutableCounter: public MutableMetric {
public:
    MutableCounter(const BasicItemReadOnly&);
public:
    void incr();
    void incr(number::Number_CRef delta);
    number::NumberPtr getValue();
protected:
    virtual void incrImpl() = 0;
    virtual void incrImpl(number::Number_CRef delta) = 0;
    virtual number::NumberPtr getValueImpl() = 0;
private:
    boost::shared_mutex value_mutex_;
};

// thread safe!
class MutableCounterInt: public MutableCounter {
public:
    MutableCounterInt(const BasicItemReadOnly& info, int init_value = 0);
protected:
    virtual void incrImpl();
    virtual void incrImpl(number::Number_CRef delta);
    virtual number::NumberPtr getValueImpl();
    virtual void snapshotImpl(MetricsRecordBuilder& builder);
private:
    int value_;
};

// thread safe!
class MutableCounterLong: public MutableCounter {
public:
    MutableCounterLong(const BasicItemReadOnly& info, long init_value = 0);
protected:
    virtual void incrImpl();
    virtual void incrImpl(number::Number_CRef delta);
    virtual number::NumberPtr getValueImpl();
    virtual void snapshotImpl(MetricsRecordBuilder& builder);
private:
    long value_;
};


//
// Gauge
//

// Thread safe!
template<class T>
class MutableGauge: public MutableMetric {
public:
    MutableGauge(const BasicItemReadOnly& info, T init_value = 0);
public:
    T value();
    void incr(T delta = 1);
    void decr(T delta = 1);
    void set(T new_value);
protected:
    virtual void snapshotImpl(MetricsRecordBuilder& builder);
private:
    T value_;
    boost::shared_mutex value_mutex_;
};

#include "MutableMetric.inl"

typedef MutableGauge<int> MutableGaugeInt;
typedef MutableGauge<long> MutableGaugeLong;
typedef MutableGauge<float> MutableGaugeFloat;
typedef MutableGauge<double> MutableGaugeDouble;

} /* namespace gmf */
#endif /* MUTABLEMETRIC_H_ */
