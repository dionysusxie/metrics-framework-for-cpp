/*
 * MetricsSystem.h
 *
 *  Created on: Jun 4, 2013
 *      Author: xieliang
 */

#ifndef METRICSSYSTEM_H_
#define METRICSSYSTEM_H_

#include <boost/shared_ptr.hpp>
#include "gmf_common.h"
#include "MetricsSource.h"
#include "MetricsSink.h"


namespace gmf {

class MetricsSystem {
public:
    static boost::shared_ptr<MetricsSystem> getSingleton();

public:
    virtual ~MetricsSystem();
    bool config();
    bool registerSource(boost::shared_ptr<MetricsSource>);
    bool registerSink(boost::shared_ptr<MetricsSink>);
    void start();
    void stop();

private:
    MetricsSystem();

private:
    static boost::shared_ptr<MetricsSystem> s_pSingleton;
};

} /* namespace gmf */
#endif /* METRICSSYSTEM_H_ */
