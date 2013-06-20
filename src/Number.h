/*
 * Number.h
 *
 *  Created on: Jun 19, 2013
 *      Author: xieliang
 */

#ifndef NUMBER_H_
#define NUMBER_H_

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


class Int: public Number {
public:
    Int(int v);
public:
    virtual int intValue() const;
    virtual long longValue() const;
    virtual float floatValue() const;
    virtual double doubleValue() const;
private:
    int value_;
};

} /* namespace number */
} /* namespace gmf */
#endif /* NUMBER_H_ */
