/*
 * BasicItem.cpp
 *
 *  Created on: May 30, 2013
 *      Author: xieliang
 */

#include "BasicItem.h"

using namespace std;

namespace gmf {

BasicItem::BasicItem(const std::string& name, const std::string& desc) {
    // TODO Auto-generated constructor stub
    this->name_ = name;
    this->description_ = desc;
}

BasicItem::~BasicItem() {
    // TODO Auto-generated destructor stub
}

void BasicItem::setName(const std::string& name) {
    this->name_ = name;
}

void BasicItem::setDescription(const std::string& desc) {
    this->description_ = desc;
}

std::string BasicItem::getName() const {
    return this->name_;
}

std::string BasicItem::getDescription() const {
    return this->description_;
}

} /* namespace gmf */
