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
    MetricSnapshot(MetricType type, const std::string& name, const std::string& desc);
    virtual ~MetricSnapshot();

public:
    MetricType getType() const;
    number::NumberCPtr getValue() const;

private:
    enum MetricType type_;
    number::NumberCPtr value_;
};

} /* namespace gmf */

#endif /* METRICSNAPSHOT_H_ */
