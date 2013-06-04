/*
 * MetricTag.h
 *
 *  Created on: Jun 3, 2013
 *      Author: xieliang
 */

#ifndef METRICTAG_H_
#define METRICTAG_H_

#include <string>
#include "BasicItem.h"

namespace gmf {

class MetricTag: public BasicItem {
public:
    MetricTag(const std::string& name, const std::string& desc, const std::string& value);
    virtual ~MetricTag();

public:
    std::string getValue() const;

private:
    const std::string value_;
};

} /* namespace gmf */
#endif /* METRICTAG_H_ */
