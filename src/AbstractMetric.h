/*
 * AbstractMetric.h
 *
 *  Created on: May 30, 2013
 *      Author: xieliang
 */

#ifndef ABSTRACTMETRIC_H_
#define ABSTRACTMETRIC_H_

#include <string>
#include "BasicItem.h"
#include "gmf_common.h"


namespace gmf {

class AbstractMetric: public BasicItem {
public:
    AbstractMetric(MetricType type, const std::string& name, const std::string& desc);
    virtual ~AbstractMetric();

public:
    MetricType getType() const;

private:
    const enum MetricType type_;
};

} /* namespace gmf */

#endif /* ABSTRACTMETRIC_H_ */
