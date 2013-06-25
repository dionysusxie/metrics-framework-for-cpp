/*
 * Number.cpp
 *
 *  Created on: Jun 19, 2013
 *      Author: xieliang
 */

#include "Number.h"

namespace gmf {
namespace number {

std::ostream& operator << (std::ostream& os, const Number& num) {
    switch (num.type()) {
    case INT:
        os << num.intValue();
        break;
    case LONG:
        os << num.longValue();
        break;
    case FLOAT:
        os << num.floatValue();
        break;
    case DOUBLE:
        os << num.doubleValue();
        break;
    default:
        BOOST_ASSERT(false);
        break;
    }

    return os;
}


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
    return static_cast<int>(this->value_);
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


//////////////////////////////////////////////////////////////////////////////////////////
//
// class Long:
//

Long::Long(long v):
        Number(LONG),
        value_(v) {
}

int Long::intValue() const {
    return static_cast<int>(this->value_);
}

long Long::longValue() const {
    return static_cast<long>(this->value_);
}

float Long::floatValue() const {
    return static_cast<float>(this->value_);
}

double Long::doubleValue() const {
    return static_cast<double>(this->value_);
}

} /* namespace number */
} /* namespace gmf */
