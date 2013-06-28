#include "unittest.h"
#include "MetricSnapshot.h"

using namespace gmf;
using namespace gmf::number;
using namespace std;


TEST(MetricSnapshotTest, MetricCounterInt) {
    const size_t LOOP_TIMES = 100;
    for (size_t i = 0; i < LOOP_TIMES; i++) {
        const int num = rand();
        const string name("test");
        const string desc("dlkdioekld");

        MetricCounterInt m(BasicItemReadOnly(name, desc), num);

        // check name & desc:
        {
            EXPECT_EQ(name, m.getName());
            EXPECT_EQ(desc, m.getDescription());
        }

        // check metric type
        {
            EXPECT_EQ(gmf::COUNTER, m.getType());
        }

        // check metric value
        {
            ASSERT_TRUE(m.getValue().get() != NULL);
            EXPECT_EQ(number::INT, m.getValue()->type());
            EXPECT_EQ(num, m.getValue()->intValue());
            EXPECT_EQ(num, m.getRawValue());
        }
    }
}


TEST(MetricSnapshotTest, MetricCounterLong) {
    const size_t LOOP_TIMES = 100;
    for (size_t i = 0; i < LOOP_TIMES; i++) {
        const long num = rand();
        const string name("jljdj");
        const string desc("dlkdioekld");

        MetricCounterLong m(BasicItemReadOnly(name, desc), num);

        // check name & desc:
        {
            EXPECT_EQ(name, m.getName());
            EXPECT_EQ(desc, m.getDescription());
        }

        // check metric type
        {
            EXPECT_EQ(gmf::COUNTER, m.getType());
        }

        // check metric value
        {
            ASSERT_TRUE(m.getValue().get() != NULL);
            EXPECT_EQ(number::LONG, m.getValue()->type());
            EXPECT_EQ(num, m.getValue()->longValue());
            EXPECT_EQ(num, m.getRawValue());
        }
    }
}


TEST(MetricSnapshotTest, MetricGaugeInt) {
    const size_t LOOP_TIMES = 100;
    for (size_t i = 0; i < LOOP_TIMES; i++) {
        const int num = rand();
        const string name("test");
        const string desc("dlkdioekld");

        MetricGaugeInt m(BasicItemReadOnly(name, desc), num);

        // check name & desc:
        {
            EXPECT_EQ(name, m.getName());
            EXPECT_EQ(desc, m.getDescription());
        }

        // check metric type
        {
            EXPECT_EQ(gmf::GAUGE, m.getType());
        }

        // check metric value
        {
            ASSERT_TRUE(m.getValue().get() != NULL);
            EXPECT_EQ(number::INT, m.getValue()->type());
            EXPECT_EQ(num, m.getValue()->intValue());
            EXPECT_EQ(num, m.getRawValue());
        }
    }
}


TEST(MetricSnapshotTest, MetricGaugeLong) {
    const size_t LOOP_TIMES = 100;
    for (size_t i = 0; i < LOOP_TIMES; i++) {
        const long num = rand();
        const string name("test");
        const string desc("dlkdioekld");

        MetricGaugeLong m(BasicItemReadOnly(name, desc), num);

        // check name & desc:
        {
            EXPECT_EQ(name, m.getName());
            EXPECT_EQ(desc, m.getDescription());
        }

        // check metric type
        {
            EXPECT_EQ(gmf::GAUGE, m.getType());
        }

        // check metric value
        {
            ASSERT_TRUE(m.getValue().get() != NULL);
            EXPECT_EQ(number::LONG, m.getValue()->type());
            EXPECT_EQ(num, m.getValue()->longValue());
            EXPECT_EQ(num, m.getRawValue());
        }
    }
}


TEST(MetricSnapshotTest, MetricGaugeFloat) {
    const size_t LOOP_TIMES = 100;
    for (size_t i = 0; i < LOOP_TIMES; i++) {
        const float num = rand() + 0.5454;
        const string name("test");
        const string desc("dlkdioekld");

        MetricGaugeFloat m(BasicItemReadOnly(name, desc), num);

        // check name & desc:
        {
            EXPECT_EQ(name, m.getName());
            EXPECT_EQ(desc, m.getDescription());
        }

        // check metric type
        {
            EXPECT_EQ(gmf::GAUGE, m.getType());
        }

        // check metric value
        {
            ASSERT_TRUE(m.getValue().get() != NULL);
            EXPECT_EQ(number::FLOAT, m.getValue()->type());
            EXPECT_FLOAT_EQ(num, m.getValue()->floatValue());
            EXPECT_FLOAT_EQ(num, m.getRawValue());
        }
    }
}


TEST(MetricSnapshotTest, MetricGaugeDouble) {
    const size_t LOOP_TIMES = 100;
    for (size_t i = 0; i < LOOP_TIMES; i++) {
        const double num = rand() + 0.5454;
        const string name("test");
        const string desc("dlkdioekld");

        MetricGaugeDouble m(BasicItemReadOnly(name, desc), num);

        // check name & desc:
        {
            EXPECT_EQ(name, m.getName());
            EXPECT_EQ(desc, m.getDescription());
        }

        // check metric type
        {
            EXPECT_EQ(gmf::GAUGE, m.getType());
        }

        // check metric value
        {
            ASSERT_TRUE(m.getValue().get() != NULL);
            EXPECT_EQ(number::DOUBLE, m.getValue()->type());
            EXPECT_DOUBLE_EQ(num, m.getValue()->doubleValue());
            EXPECT_DOUBLE_EQ(num, m.getRawValue());
        }
    }
}

