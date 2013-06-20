/*
 * Number.cpp
 *
 *  Created on: Jun 19, 2013
 *      Author: xieliang
 */

#include "Number.h"

namespace gmf {
namespace number {

//////////////////////////////////////////////////////////////////////////////////////////
//
// class Number:
//

Number::Number(NumType t):
        type_(t) {
}

Number::~Number() {
}

NumType Number::type() const {
    return this->type_;
}


//////////////////////////////////////////////////////////////////////////////////////////
//
// class Int:
//

Int::Int(int v):
        Number(INT),
        value_(v) {
}

int Int::intValue() const {
    return this->value_;
}

long Int::longValue() const {
    return static_cast<long>(this->value_);
}

float Int::floatValue() const {
    return static_cast<float>(this->value_);
}

double Int::doubleValue() const {
    return static_cast<double>(this->value_);
}


} /* namespace number */
} /* namespace gmf */
