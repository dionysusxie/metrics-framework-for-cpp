/*
 * BasicItem.cpp
 *
 *  Created on: May 30, 2013
 *      Author: xieliang
 */

#include "BasicItem.h"

using namespace std;

namespace gmf {

/////////////////////////////////////////////////////////////////////////////////////////
//
// class BasicItemReadOnly:
//

const std::string BasicItemReadOnly::DEF_NAME = "none";
const std::string BasicItemReadOnly::DEF_DESC = "none";

BasicItemReadOnly::BasicItemReadOnly(const std::string& name, const std::string& desc):
    name_(name),
    description_(desc) {
}

BasicItemReadOnly::~BasicItemReadOnly() {
}

std::string BasicItemReadOnly::getName() const {
    return this->name_;
}

std::string BasicItemReadOnly::getDescription() const {
    return this->description_;
}


/////////////////////////////////////////////////////////////////////////////////////////
//
// class BasicItem:
//

BasicItem::BasicItem(const std::string& name, const std::string& desc):
        name_(name),
        description_(desc) {
}

BasicItem::BasicItem(const BasicItemReadOnly& info):
    name_(info.getName()),
    description_(info.getDescription()) {
}

BasicItem::~BasicItem() {
}

std::string BasicItem::getName() {
    boost::shared_lock<boost::shared_mutex> read_lock(this->name_mutex_);
    return this->name_;
}

void BasicItem::setName(const std::string& name) {
    boost::lock_guard<boost::shared_mutex> write_lock(this->name_mutex_);
    this->name_ = name;
}

std::string BasicItem::getDescription() {
    boost::shared_lock<boost::shared_mutex> read_lock(this->description_mutex_);
    return this->description_;
}

void BasicItem::setDescription(const std::string& desc) {
    boost::lock_guard<boost::shared_mutex> write_lock(this->description_mutex_);
    this->description_ = desc;
}

BasicItemReadOnly BasicItem::getReadOnlyItem() {
    return BasicItemReadOnly(getName(), getDescription());
}

} /* namespace gmf */
