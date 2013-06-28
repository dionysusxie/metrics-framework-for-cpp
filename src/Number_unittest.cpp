/*
 * Number_unittest.cpp
 *
 *  Created on: Jun 27, 2013
 *      Author: xieliang
 */

#include "unittest.h"
#include "Number.h"

using namespace gmf;
using namespace gmf::number;
using namespace std;


TEST(NumberTest, Int) {
    const size_t LOOP_TIMES = 100;
    for (size_t i = 0; i < LOOP_TIMES; i++) {
        const int num = rand();

        Int a(num);
        EXPECT_EQ(num, a.value());
        EXPECT_EQ(INT, a.type());
        EXPECT_EQ(a.value(), a.intValue());

        NumberPtr pnum = Number::newNumber(num);
        ASSERT_TRUE(pnum.get() != NULL);
        EXPECT_EQ(INT, pnum->type());
        EXPECT_EQ(num, pnum->intValue());
    }
}

TEST(NumberTest, Long) {
    const size_t LOOP_TIMES = 100;
    for (size_t i = 0; i < LOOP_TIMES; i++) {
        const long num = (long)rand();

        Long a(num);
        EXPECT_EQ(num, a.value());
        EXPECT_EQ(LONG, a.type());
        EXPECT_EQ(a.value(), a.longValue());

        NumberPtr pnum = Number::newNumber(num);
        ASSERT_TRUE(pnum.get() != NULL);
        EXPECT_EQ(LONG, pnum->type());
        EXPECT_EQ(num, pnum->longValue());
    }
}

TEST(NumberTest, Float) {
    const size_t LOOP_TIMES = 100;
    for (size_t i = 0; i < LOOP_TIMES; i++) {
        const float num = rand() + 0.12345;

        Float a(num);
        EXPECT_TRUE(float_equal(num, a.value()));
        EXPECT_TRUE(float_equal(a.value(), a.floatValue()));
        EXPECT_EQ(FLOAT, a.type());

        NumberPtr pnum = Number::newNumber(num);
        ASSERT_TRUE(pnum.get() != NULL);
        EXPECT_EQ(FLOAT, pnum->type());
        EXPECT_TRUE(float_equal(num, pnum->floatValue()));
    }
}

TEST(NumberTest, Double) {
    const size_t LOOP_TIMES = 100;
    for (size_t i = 0; i < LOOP_TIMES; i++) {
        const double num = rand() + 0.12345;

        Double a(num);
        EXPECT_TRUE(float_equal(num, a.value()));
        EXPECT_TRUE(float_equal(a.value(), a.doubleValue()));
        EXPECT_EQ(DOUBLE, a.type());

        NumberPtr pnum = Number::newNumber(num);
        ASSERT_TRUE(pnum.get() != NULL);
        EXPECT_EQ(DOUBLE, pnum->type());
        EXPECT_TRUE(float_equal(num, pnum->doubleValue()));
    }
}

