/*
 * BasicItem.h
 *
 *  Created on: May 30, 2013
 *      Author: xieliang
 */

#ifndef BASICITEM_H_
#define BASICITEM_H_

#include <string>
#include <boost/thread.hpp>

namespace gmf {

// This class is thread-safe!
class BasicItemReadOnly {
public:
    static const std::string DEF_NAME;
    static const std::string DEF_DESC;
public:
    BasicItemReadOnly(const std::string& name = DEF_NAME, const std::string& desc = DEF_DESC);
    virtual ~BasicItemReadOnly();
public:
    std::string getName() const;
    std::string getDescription() const;
private:
    std::string name_;
    std::string description_;
};

// This class is thread-safe!
class BasicItem {
public:
    BasicItem(const std::string& name = "", const std::string& desc = "");
    virtual ~BasicItem();
public:
    std::string getName();
    void setName(const std::string&);

    std::string getDescription();
    void setDescription(const std::string&);

    BasicItemReadOnly getReadOnlyItem();
private:
    std::string name_;
    boost::shared_mutex name_mutex_;

    std::string description_;
    boost::shared_mutex description_mutex_;
};

} /* namespace gmf */
#endif /* BASICITEM_H_ */
