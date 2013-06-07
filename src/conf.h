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

//
// NOTE:
// 1. It's modified by Xieliang to be used in the project "scribekeeper"
// 2. It uses the log system(defined in log.h) to output the logs
// 3. Normal logs will be handled by LOG_INFO(), and error-messages by LOG_ERROR()
//


#ifndef SCRIBE_CONF_H
#define SCRIBE_CONF_H

#include <boost/shared_ptr.hpp>
#include <map>
#include <vector>
#include <queue>
#include <stdint.h>
#include <string>


/*lu
 * This class reads and parses a configuration
 * describing a hierarchy of store objects.
 *
 * It reads a conf file with a proprietary format, although it could
 * be changed to xml (or anything else that supports hierarchy) by only
 * changing the code in this class.
 */

class StoreConf;
typedef boost::shared_ptr<StoreConf> StoreConfPtr;
typedef std::map<std::string, std::string> STR_STR_MAP;
typedef std::map<std::string, StoreConfPtr> STR_CONF_MAP;


std::ostream& operator << (std::ostream& os, const StoreConf& storeConf);


class StoreConf {
    friend std::ostream& operator << (std::ostream& os, const StoreConf& storeConf);

public:
    StoreConf();
    StoreConf(const StoreConf& other);
    virtual ~StoreConf();
    StoreConf& operator = (const StoreConf& other);

    // Return value is true if the key exists, and false if it doesn't.
    // This doesn't check for garbage ints or empty strings.
    // The return parameter is untouched if the key isn't found.
    void getAllStores(std::vector<StoreConfPtr>& _return) const;
    void getAllKeys(std::vector<std::string>& _return) const;
    void getAllValues(STR_STR_MAP& _return) const;
    bool getStore(const std::string& storeName, StoreConfPtr& _return) const;
    bool getInt(const std::string& intName, int& _return) const;
    bool getLong(const std::string& intName, long int& _return) const;
    bool getUnsigned(const std::string& intName, unsigned long int& _return) const;
    bool getUnsignedLongLong(const std::string& intName, unsigned long long& _return) const;
    bool getFloat(const std::string& floatName, float & _return) const;
    bool getString(const std::string& stringName, std::string& _return) const;

    void setString(const std::string& stringName, const std::string& value);
    void setUnsigned(const std::string& intName, unsigned long value);
    void setUnsignedLongLong(const std::string& intName, unsigned long long value);

    bool parseConfig(const std::string& filename);

    std::string getName() const;
    void setName(const std::string& ss);

    void setParent(StoreConf* parent);

private:
    STR_STR_MAP values;
    STR_CONF_MAP stores;
    StoreConf* parent;
    std::string name;

    static bool parseStore(/*in,out*/std::queue<std::string>& raw_config,
            /*out*/StoreConf* parsed_config);

    static std::string trim(const std::string& str);
    static std::string trimLeft(const std::string& str);
    static std::string trimRight(const std::string& str);


    bool readConfFile(const std::string& filename, std::queue<std::string>& _return);
    std::ostream& print(std::ostream& os, uint32_t depth, bool useSpace = true, uint32_t tabw = 2) const;
};

#endif //!defined SCRIBE_CONF_H
