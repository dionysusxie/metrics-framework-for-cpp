//  Copyright (c) 2007-2008 Facebook
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//
// See accompanying file LICENSE or visit the Scribe site at:
// http://developers.facebook.com/scribe/
//
// @author Bobby Johnson
// @author Jason Sobel
// @author John Song

#include <boost/algorithm/string.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <allyes-log.h>
#include "conf.h"

using namespace boost;
using namespace std;

static const std::string REPEATABLE_STORE[] = {
    "source",
    "sink",
};

StoreConf::StoreConf():
    parent(NULL),
    name("none") {
}

StoreConf::StoreConf(const StoreConf& other) {
    *this = other;
}

StoreConf::~StoreConf() {
}

StoreConf& StoreConf::operator = (const StoreConf& other) {
    if (this == &other) {
        return *this;
    }

    name = other.name;
    parent = other.parent;
    values = other.values;
    stores = other.stores;

    for (STR_CONF_MAP::iterator it = stores.begin(); it != stores.end(); it++) {
        it->second->setParent(this);
    }

    return *this;
}

bool StoreConf::getStore(const string& storeName, StoreConfPtr& _return) const {
    STR_CONF_MAP::const_iterator iter = stores.find(storeName);
    if (iter != stores.end()) {
        _return = iter->second;
        return true;
    }
    else {
        return false;
    }
}

std::string StoreConf::getName() const {
    return name;
}

void StoreConf::setName(const std::string& ss) {
    name = ss;
}

void StoreConf::setParent(ptrStoreConf pParent) {
    parent = pParent;
}

void StoreConf::getAllStores(vector<StoreConfPtr>& _return) const {
    for (STR_CONF_MAP::const_iterator iter = stores.begin(); iter != stores.end(); ++iter) {
        _return.push_back(iter->second);
    }
}

void StoreConf::getAllKeys(std::vector<std::string>& _return) const {
	for (STR_STR_MAP::const_iterator cit = values.begin(); cit != values.end(); cit++) {
		_return.push_back(cit->first);
	}
}

void StoreConf::getAllValues(STR_STR_MAP& _return) const {
	_return = values;
}

bool StoreConf::getInt(const string& intName, int& _return) const {
    string str;
    if (getString(intName, str)) {
        _return = atoi(str.c_str());
        return true;
    }
    else {
        return false;
    }
}

bool StoreConf::getLong(const string& intName, long int& _return) const {
    string str;
    if (getString(intName, str)) {
        _return = strtol(str.c_str(), NULL, 0);
        return true;
    }
    else {
        return false;
    }
}

bool StoreConf::getFloat(const std::string& floatName, float & _return) const {
    string str;
    if (getString(floatName, str)) {
        _return = strtof(str.c_str(), NULL);
        return true;
    }
    else {
        return false;
    }
}

bool StoreConf::getUnsigned(const string& intName,
        unsigned long int& _return) const {
    string str;
    if (getString(intName, str)) {
        _return = strtoul(str.c_str(), NULL, 0);
        return true;
    }
    else {
        return false;
    }
}

bool StoreConf::getUnsignedLongLong(const string& llName,
        unsigned long long& _return) const {
    string str;
    if (getString(llName, str)) {
        _return = strtoull(str.c_str(), NULL, 10);
        return true;
    }
    else {
        return false;
    }
}

bool StoreConf::getString(const string& stringName, string& _return) const {
    STR_STR_MAP::const_iterator iter = values.find(stringName);

    if (iter != values.end()) {
        _return = iter->second;
        return true;
    }

    return false;
}

void StoreConf::setString(const string& stringName, const string& value) {
    values[stringName] = value;
}

void StoreConf::setUnsigned(const string& stringName, unsigned long value) {
    ostringstream oss;
    oss << value;
    setString(stringName, oss.str());
}

void StoreConf::setUnsignedLongLong(const string& stringName, unsigned long long value) {
    ostringstream oss;
    oss << value;
    setString(stringName, oss.str());
}

// reads and parses the config data
bool StoreConf::parseConfig(const string& filename) {

    queue<string> config_strings;

    if (readConfFile(filename, config_strings)) {
        LOG_INFO("got configuration data from file <%s>", filename.c_str());
        return parseStore(config_strings, this);
    }
    else {
        LOG_ERROR("Failed to open config file <%s>", filename.c_str());
        return false;
    }
}

// Side-effects:  - removes items from raw_config and adds items to parsed_config
//
// Returns true if a valid entry was found
bool StoreConf::parseStore(queue<string>& raw_config, /*out*/ptrStoreConf parsed_config) {
    std::map<std::string, int> repeated_item;
    for(unsigned int i=0; i<sizeof(REPEATABLE_STORE)/sizeof(REPEATABLE_STORE[0]); ++i) {
        repeated_item[REPEATABLE_STORE[i]] = 0;
    }
    
    string line;
    while (!raw_config.empty()) {

        line = raw_config.front();
        raw_config.pop();

        // remove leading and trailing whitespace
        line = trim(line);

        // remove comment
        size_t comment = line.find_first_of('#');
        if (comment != string::npos) {
            line.erase(comment);
        }

        line = trim(line);

        const int length = line.size();
        if (length < 1) {
            continue;
        }

        if ('<' == line[0]) {

            if (length > 1 && '/' == line[1]) {
                // This is the end of the current store
                return true;
            }

            // This is the start of a new store
            string::size_type pos = line.find('>');
            if (string::npos == pos) {
                LOG_ERROR("Bad config - the line has a < but without a >: %s", line.c_str());
                return false;
            }
            string store_name = line.substr(1, pos - 1);
            store_name = trim(store_name);

            StoreConfPtr new_store(new StoreConf);

            if (parseStore(raw_config, new_store.get())) {
                std::map<std::string, int>::iterator itor = repeated_item.find(store_name);
                if(itor != repeated_item.end()) {
                    ostringstream oss;
                    oss << itor->second;
                    store_name += oss.str();
                    ++itor->second;
                }
                if (parsed_config->stores.find(store_name) != parsed_config->stores.end()) {
                    LOG_ERROR("Bad config - duplicate store name: %s", store_name.c_str());
                    return false;
                }

                parsed_config->stores[store_name] = new_store;
                new_store->setParent(parsed_config);
                new_store->setName(store_name);
            }
            else {
                return false;
            }

        }
        else {
            string::size_type eq = line.find('=');

            if (eq == string::npos) {
                LOG_ERROR("Bad config - line <%s> missing an =", line.c_str());
                return false;
            }

            string arg = line.substr(0, eq);
            string val = line.substr(eq + 1, string::npos);

            arg = trim(arg);
            val = trim(val);

            if (arg.empty() || val.empty()) {
                LOG_ERROR("Bad config - invalid line: %s", line.c_str());
                return false;
            }

            if (parsed_config->values.find(arg) != parsed_config->values.end()) {
                LOG_ERROR("Bad config - duplicate key: %s", arg.c_str());
                return false;
            }

            parsed_config->values[arg] = val;
        }
    }

    return true;
}

// trims leading and trailing whitespace from a string
string StoreConf::trim(const string& str) {
    string whitespace = " \t";
    size_t start = str.find_first_not_of(whitespace);
    size_t end = str.find_last_not_of(whitespace);

    if (start != string::npos) {
        return str.substr(start, end - start + 1);
    }
    else {
        return "";
    }
}

string StoreConf::trimLeft(const string& str) {
    string whitespace = " \t";
    size_t pos = str.find_first_not_of(whitespace);

    if (pos != string::npos) {
        return str.substr(pos);
    }
    else {
        return "";
    }
}

string StoreConf::trimRight(const string& str) {
    string whitespace = " \t";
    size_t pos = str.find_last_not_of(whitespace);

    if (pos != string::npos) {
        return str.substr(0, pos+1);
    }
    else {
        return "";
    }
}

// reads every line from the file and pushes then onto _return
// returns false on error
bool StoreConf::readConfFile(const string& filename, queue<string>& _return) {
    ifstream config_file;
    config_file.open(filename.c_str());
    if (!config_file.good()) {
        return false;
    }

    string last_line;       bool last_line_to_be_continued = true;
    string current_line;    bool current_line_to_be_continued;

    while (getline(config_file, current_line)) {
        current_line = trimRight(current_line);
        if(!current_line.empty() && current_line[current_line.size()-1] == '\\') {
            current_line_to_be_continued = true;
            current_line.erase(current_line.end()-1);
        }
        else {
            current_line_to_be_continued = false;
        }

        if (last_line_to_be_continued) {
            last_line.append(current_line);
            if(!current_line_to_be_continued) {
                _return.push(last_line);
                last_line.clear();
            }
        }
        else {
            if(current_line_to_be_continued) {
                last_line = current_line;
            }
            else {
                _return.push(current_line);
            }
        }

        last_line_to_be_continued = current_line_to_be_continued;
    }

    if (last_line_to_be_continued) {
        _return.push(last_line);
    }

    config_file.close();

#if 0
    {
        /// for checking ///
        queue<string> tmp_queue(_return);
        while (!tmp_queue.empty()) {
            const string line = tmp_queue.front();
            tmp_queue.pop();
            cout << line << endl;
        }
        /// end checking ///
    }
#endif

    return true;
}

// serialize StoreConf
ostream& operator << (ostream& os, const StoreConf& sconf) {
    return sconf.print(os, 0);
}

static string indent(uint32_t depth, bool useSpace, uint32_t tabw) {
    int len = useSpace ? depth * tabw : depth;
    return string(len, useSpace ? ' ' : '\t');
}

ostream& StoreConf::print(ostream& os, uint32_t depth,
        bool useSpace, uint32_t tabw) const {
    // we only need to iterator through keys. as map guaranteed keys
    // are weakly ordered, so we will get consistent output.
    for (STR_STR_MAP::const_iterator iter = values.begin();
            iter != values.end();
            iter++) {
        // int len = useSpace ? depth * tabw : depth;
        os << indent(depth, useSpace, tabw) << iter->first << "=" << iter->second << endl;
    }

    // print out sub stores
    for (STR_CONF_MAP::const_iterator iter = stores.begin();
            iter != stores.end();
            iter++) {
        os << indent(depth, useSpace, tabw) << "<" << iter->first << ">" << endl;
        iter->second->print(os, depth + 1, useSpace, tabw);
        os << indent(depth, useSpace, tabw) << "</" << iter->first << ">" << endl;
    }

    return os;
}
