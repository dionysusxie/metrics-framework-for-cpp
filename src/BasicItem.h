/*
 * BasicItem.h
 *
 *  Created on: May 30, 2013
 *      Author: xieliang
 */

#ifndef BASICITEM_H_
#define BASICITEM_H_

#include <string>


namespace gmf {

class BasicItemReadOnly {
public:
    BasicItemReadOnly(const std::string& name, const std::string& desc);
    virtual ~BasicItemReadOnly();
public:
    std::string getName() const;
    std::string getDescription() const;
protected:
    std::string name_;
    std::string description_;
};

class BasicItem: public BasicItemReadOnly {
public:
    BasicItem(const std::string& name = "none", const std::string& desc = "none");
    virtual ~BasicItem();
public:
    void setName(const std::string&);
    void setDescription(const std::string&);
};

} /* namespace gmf */
#endif /* BASICITEM_H_ */
