/*
 * MutableMetric_unittest.cpp
 *
 *  Created on: Jul 1, 2013
 *      Author: xieliang
 */


#include "unittest.h"
#include "MutableMetric.h"
#include "Number.h"

using namespace gmf;
using namespace std;


//
// helpers functions:
//

void MY_EXPECT_EQ(int expected, int real) {
    EXPECT_EQ(expected, real);
}

void MY_EXPECT_EQ(long expected, long real) {
    EXPECT_EQ(expected, real);
}

void MY_EXPECT_EQ(float expected, float real) {
    EXPECT_FLOAT_EQ(expected, real);
}

void MY_EXPECT_EQ(double expected, double real) {
    EXPECT_DOUBLE_EQ(expected, real);
}


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


//
// 测试模版类 MutableGauge
//

template <class T>
class MutableGaugeTest: public ::testing::Test {
private:
    MutableGauge<T> m_;
public:
    MutableGaugeTest():
        m_(BasicItemReadOnly(), (T)(rand() + 0.0001)) {
    }
    void check() {
        checkType();
        checkInit();
        checkIncr();
        checkDecr();
        checkSet();
    }
protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
private:
    void checkType() {
        ::testing::StaticAssertTypeEq<T, typename MutableGauge<T>::VALUE_TYPE>();
    }

    void checkInit() {
        const T init_val = (T)rand();
        MutableGauge<T> counter(BasicItemReadOnly(), init_val);
        MY_EXPECT_EQ(init_val, counter.value());
    }

    void checkIncr() {
        const size_t LOOP_TIMES = 100;

        // incr()
        for (size_t i = 0; i < LOOP_TIMES; i++) {
            const T old_val = m_.value();
            m_.incr();
            MY_EXPECT_EQ((old_val + 1), m_.value());
        }

        // incr(x)
        for (size_t i = 0; i < LOOP_TIMES; i++) {
            const T old_val = m_.value();
            const T DELTA = rand();
            m_.incr(DELTA);
            MY_EXPECT_EQ((old_val + DELTA), m_.value());
        }
    }

    void checkDecr() {
        const size_t LOOP_TIMES = 100;

        // desc()
        for (size_t i = 0; i < LOOP_TIMES; i++) {
            const T old_val = m_.value();
            m_.decr();
            MY_EXPECT_EQ((old_val - 1), m_.value());
        }

        // desc(x)
        for (size_t i = 0; i < LOOP_TIMES; i++) {
            const T old_val = m_.value();
            const T DELTA = (T)rand();
            m_.decr(DELTA);
            MY_EXPECT_EQ((old_val - DELTA), m_.value());
        }
    }

    void checkSet() {
        const size_t LOOP_TIMES = 100;
        for (size_t i = 0; i < LOOP_TIMES; i++) {
            const T new_val = (T)rand();
            this->m_.set(new_val);
            MY_EXPECT_EQ(new_val, m_.value());
        }
    }
};

typedef MutableGaugeTest<int> MutableGaugeTestInt;
typedef MutableGaugeTest<long> MutableGaugeTestLong;
typedef MutableGaugeTest<float> MutableGaugeTestFloat;
typedef MutableGaugeTest<double> MutableGaugeTestDouble;

TEST_F(MutableGaugeTestInt, check) {
    check();
}

TEST_F(MutableGaugeTestLong, check) {
    check();
}

TEST_F(MutableGaugeTestFloat, check) {
    check();
}

TEST_F(MutableGaugeTestDouble, check) {
    check();
}


//
// Test 4 class instantiated from MutableGauge:
//

TEST(MutableGaugeInt, TypeCheck) {
    ::testing::StaticAssertTypeEq<int, typename MutableGaugeInt::VALUE_TYPE>();
}

TEST(MutableGaugeLong, TypeCheck) {
    ::testing::StaticAssertTypeEq<long, typename MutableGaugeLong::VALUE_TYPE>();
}

TEST(MutableGaugeFloat, TypeCheck) {
    ::testing::StaticAssertTypeEq<float, typename MutableGaugeFloat::VALUE_TYPE>();
}

TEST(MutableGaugeDouble, TypeCheck) {
    ::testing::StaticAssertTypeEq<double, typename MutableGaugeDouble::VALUE_TYPE>();
}

