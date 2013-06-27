/*
 * Number_unittest.cpp
 *
 *  Created on: Jun 27, 2013
 *      Author: xieliang
 */


#include <cmath>
#include <gtest/gtest.h>
#include "Number.h"

using namespace gmf;
using namespace gmf::number;
using namespace std;

template<class T>
bool float_equal(T a, T b) {
    const T small = 0.00001;
    return std::abs(a - b) < small;
}

TEST(NumberTest, Int) {
    Int a(1);
    EXPECT_EQ(1, a.value());
    EXPECT_EQ(INT, a.type());
}

TEST(NumberTest, Long) {
    Long a(1);
    EXPECT_EQ(1, a.value());
    EXPECT_EQ(LONG, a.type());
}

TEST(NumberTest, Float) {
    const float num = 1.0002;
    Float a(num);

    EXPECT_TRUE(float_equal(num, a.value()));
    EXPECT_EQ(FLOAT, a.type());
}

TEST(NumberTest, Double) {
    const double num = 1.0002;
    Double a(num);

    EXPECT_TRUE(float_equal(num, a.value()));
    EXPECT_EQ(DOUBLE, a.type());
}
