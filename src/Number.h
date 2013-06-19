/*
 * Number.h
 *
 *  Created on: Jun 19, 2013
 *      Author: xieliang
 */

#ifndef NUMBER_H_
#define NUMBER_H_

namespace gmf {

class Number {
public:
    enum NumType {
        SHORT = 0,
        INT,
        LONG,
        FLOAT,
        DOUBLE,
        MAX
    };
public:
    Number();
    virtual ~Number();
public:
    virtual short shortValue() const = 0;
    virtual int intValue() const = 0;
    virtual long longValue() const = 0;
    virtual float floatValue() const = 0;
    virtual double doubleValue() const = 0;

    NumType type() const;
private:
    NumType type_;
};

} /* namespace gmf */
#endif /* NUMBER_H_ */
