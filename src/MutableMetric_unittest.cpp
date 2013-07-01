/*
 * MutableMetric_unittest.cpp
 *
 *  Created on: Jul 1, 2013
 *      Author: xieliang
 */


#include "unittest.h"
#include "MutableMetric.h"

using namespace gmf;
using namespace std;


TEST(MutableMetric, MutableCounterInt) {
    const int init_val = rand();
    MutableCounterInt counter(BasicItemReadOnly(), init_val);

    // type check
    {
        ::testing::StaticAssertTypeEq<int, MutableCounterInt::VALUE_TYPE>();
    }

    // check initia value
    {
        EXPECT_EQ(init_val, counter.value());
    }

    // incr()
    {
        const size_t LOOP_TIMES = 100;
        for (size_t i = 0; i < LOOP_TIMES; i++) {
            const int old_val = counter.value();
            counter.incr();
            EXPECT_EQ((old_val + 1), counter.value());
        }
    }

    // incr(x)
    {
        const size_t LOOP_TIMES = 100;
        for (size_t i = 0; i < LOOP_TIMES; i++) {
            const int old_val = counter.value();

            const int DELTA = rand();
            counter.incr(DELTA);

            EXPECT_EQ((old_val + DELTA), counter.value());
        }
    }
}


TEST(MutableMetric, MutableCounterLong) {
    const long init_val = rand();
    MutableCounterLong counter(BasicItemReadOnly(), init_val);

    // type check
    {
        ::testing::StaticAssertTypeEq<long, MutableCounterLong::VALUE_TYPE>();
    }

    // check initia value
    {
        EXPECT_EQ(init_val, counter.value());
    }

    // incr()
    {
        const size_t LOOP_TIMES = 100;
        for (size_t i = 0; i < LOOP_TIMES; i++) {
            const long old_val = counter.value();
            counter.incr();
            EXPECT_EQ((old_val + 1), counter.value());
        }
    }

    // incr(x)
    {
        const size_t LOOP_TIMES = 100;
        for (size_t i = 0; i < LOOP_TIMES; i++) {
            const long old_val = counter.value();

            const long DELTA = rand();
            counter.incr(DELTA);

            EXPECT_EQ((old_val + DELTA), counter.value());
        }
    }
}
