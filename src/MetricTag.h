/*
 * MetricTag.h
 *
 *  Created on: Jun 3, 2013
 *      Author: xieliang
 */

#ifndef METRICTAG_H_
#define METRICTAG_H_

#include <string>
#include "gmf_common.h"
#include "BasicItem.h"

namespace gmf {

class MetricTag;
typedef boost::shared_ptr<MetricTag> MetricTagPtr;
typedef boost::shared_ptr<const MetricTag> ConstMetricTagPtr;
typedef ConstMetricTagPtr MetricTagCPtr;

class MetricTag: public BasicItemReadOnly {
public:
    MetricTag(const std::string& name = "", const std::string& desc = "",
            const std::string& value = "");
    virtual ~MetricTag();

public:
    std::string getValue() const;

private:
    std::string value_;
};

} /* namespace gmf */
#endif /* METRICTAG_H_ */
