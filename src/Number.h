/*
 * Number.h
 *
 *  Created on: Jun 19, 2013
 *      Author: xieliang
 */

#ifndef NUMBER_H_
#define NUMBER_H_

#include <iostream>
#include "gmf_common.h"

namespace gmf {
namespace number {

enum NumType {
    INT = 0,
    LONG,
    FLOAT,
    DOUBLE,
    MAX
};


class Number;
typedef boost::shared_ptr<Number> NumberPtr;
typedef boost::shared_ptr<const Number> NumberCPtr;
typedef const Number& Number_CRef;

extern std::ostream& operator << (std::ostream& os, const Number& num);


class Number {
public:
    Number(NumType t);
    virtual ~Number();
public:
    virtual int intValue() const = 0;
    virtual long longValue() const = 0;
    virtual float floatValue() const = 0;
    virtual double doubleValue() const = 0;

    NumType type() const;
private:
    NumType type_;
};


template<class DATA_TYPE, NumType ENUM_TYPE>
class NumberTpl: public Number {
public:
    NumberTpl(DATA_TYPE val):
        Number(ENUM_TYPE),
        value_(val) {
    }
public:
    virtual int intValue() const {
        return static_cast<int>(this->value_);
    }
    virtual long longValue() const {
        return static_cast<long>(this->value_);
    }
    virtual float floatValue() const {
        return static_cast<float>(this->value_);
    }
    virtual double doubleValue() const {
        return static_cast<double>(this->value_);
    }
private:
    DATA_TYPE value_;
};

typedef NumberTpl<int, INT> Int;
typedef NumberTpl<long, LONG> Long;
typedef NumberTpl<float, FLOAT> Float;
typedef NumberTpl<double, DOUBLE> Double;

} /* namespace number */
} /* namespace gmf */
#endif /* NUMBER_H_ */
