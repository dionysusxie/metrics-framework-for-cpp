/*
 * Number_unittest.cpp
 *
 *  Created on: Jun 27, 2013
 *      Author: xieliang
 */



#include <gtest/gtest.h>
#include "Number.h"

using namespace gmf;
using namespace gmf::number;

TEST(NumberTest, Int) {
    Int a(1);
    EXPECT_EQ(1, a.intValue());
}
