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
    void snapshot(MetricsRecordBuilder& builder, bool all);
    void snapshot(MetricsRecordBuilder& builder);
    bool changed();
protected:
    virtual void snapshotImpl(MetricsRecordBuilder& builder) = 0;
    void setChanged();
    void clearChanged();
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

class MutableGauge: public MutableMetric {
public:
    MutableGauge(const BasicItemReadOnly& info);
public:
    number::NumberPtr getValue();
    void incr();
    void incr(number::Number_CRef delta);
    void decr();
    void decr(number::Number_CRef delta);
    void set(number::Number_CRef new_value);
protected:
    virtual number::NumberPtr getValueImpl() = 0;
    virtual void incrImpl() = 0;
    virtual void incrImpl(number::Number_CRef delta) = 0;
    virtual void decrImpl() = 0;
    virtual void decrImpl(number::Number_CRef delta) = 0;
    virtual void setImpl(number::Number_CRef new_value) = 0;
private:
    boost::shared_mutex value_mutex_;
};

} /* namespace gmf */
#endif /* MUTABLEMETRIC_H_ */
