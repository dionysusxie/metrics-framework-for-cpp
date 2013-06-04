/*
 * Updater.h
 *
 *  Created on: May 23, 2013
 *      Author: xieliang
 */

#ifndef UPDATER_H_
#define UPDATER_H_

#include "MetricsContext.h"

namespace gmf {

class Updater {
public:
    Updater();
    virtual ~Updater();

public:
    virtual void doUpdates(MetricsContext& context) = 0;
};

} /* namespace gmf */
#endif /* UPDATER_H_ */
