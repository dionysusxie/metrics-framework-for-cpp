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


namespace gmf {

class MetricSnapshot: public BasicItem {
public:
    MetricSnapshot(MetricType type, const std::string& name, const std::string& desc);
    virtual ~MetricSnapshot();

public:
    MetricType getType() const;

private:
    const enum MetricType type_;
};

} /* namespace gmf */

#endif /* METRICSNAPSHOT_H_ */
