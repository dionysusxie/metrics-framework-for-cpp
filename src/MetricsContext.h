/*
 * MetricsContext.h
 *
 *  Created on: May 23, 2013
 *      Author: xieliang
 */

#ifndef METRICSCONTEXT_H_
#define METRICSCONTEXT_H_

#include <string>


namespace gmf {

class MetricsContext {
public:
    MetricsContext();
    virtual ~MetricsContext();

public:
    //Default period in seconds at which data is sent to the metrics system.
    static const int DEFAULT_PERIOD = 10;
};

} /* namespace gmf */
#endif /* METRICSCONTEXT_H_ */
