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
        os << num.intValue() << "i";
        break;
    case LONG:
        os << num.longValue() << "l";
        break;
    case FLOAT:
        os << num.floatValue() << "f";
        break;
    case DOUBLE:
        os << num.doubleValue() << "d";
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

} /* namespace number */
} /* namespace gmf */
