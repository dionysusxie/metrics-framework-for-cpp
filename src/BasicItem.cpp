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
        BasicItemReadOnly(name, desc) {
}

BasicItem::~BasicItem() {
}

void BasicItem::setName(const std::string& name) {
    this->name_ = name;
}

void BasicItem::setDescription(const std::string& desc) {
    this->description_ = desc;
}

} /* namespace gmf */
