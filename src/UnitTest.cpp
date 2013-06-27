/*
 * test.cpp
 *
 *  For unit tests!
 *
 *  Created on: Jun 27, 2013
 *      Author: xieliang
 */

#include <time.h>       /* time */
#include "UnitTest.h"

int main(int argc, char **argv) {
    // Initialize random number generator
    {
        srand(time(NULL));
    }

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
