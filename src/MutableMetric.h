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


namespace gmf {

class MutableMetric {
public:
    MutableMetric();
    virtual ~MutableMetric();
public:
    // all: if true, snapshot unchanged metrics as well
    virtual void snapshot(MetricsRecordBuilder& builder, bool all) = 0;
    void snapshot(MetricsRecordBuilder& builder);
    bool changed();
protected:
    void setChanged();
    void clearChanged();
private:
    bool changed_;
    boost::shared_mutex changed_mutex_;
};

} /* namespace gmf */
#endif /* MUTABLEMETRIC_H_ */
