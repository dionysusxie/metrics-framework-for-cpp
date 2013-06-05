/*
 * test.cpp
 *
 *  Created on: Jun 5, 2013
 *      Author: xieliang
 */

#include <iostream>
#include "MetricsSystem.h"

using namespace std;
using namespace gmf;

int main(int argc, char* argv[]) {
    cout << "Hello world" << endl;

    MetricsSystem::getSingleton()->start();

    return 0;
}
