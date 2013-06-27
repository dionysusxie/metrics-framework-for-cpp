/*
 * UnitTest.h
 *
 *  Created on: Jun 27, 2013
 *      Author: xieliang
 */

#ifndef UNITTEST_H_
#define UNITTEST_H_

#include <gtest/gtest.h>
#include <cmath>
#include <stdlib.h>     /* srand, rand */


template<class T>
bool float_equal(T a, T b) {
    const T small = 0.00001;
    return std::abs(a - b) < small;
}

#endif /* UNITTEST_H_ */
