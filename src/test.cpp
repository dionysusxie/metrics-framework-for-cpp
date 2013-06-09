/*
 * test.cpp
 *
 *  Created on: Jun 5, 2013
 *      Author: xieliang
 */

#include <iostream>
#include <allyes-log.h>
#include <string>
#include <boost/assert.hpp>
#include <getopt.h>
#include "MetricsSystem.h"

using namespace std;
using namespace boost;
using namespace gmf;

const string DEFAULT_CONFIG_FILE("/etc/test/test.conf");
const string TXT_METRICS = "metrics";


void print_usage(const char* program_name) {
    cout << "Usage: " << program_name << " [-h] [-c config_file] [-l log_config_file] [-d]" << endl;
    cout << "Default config_file: " << DEFAULT_CONFIG_FILE << endl;
}


int main(int argc, char* argv[]) {
    try {
        int next_option;
        const char* const short_options = "hc:l:d";
        const struct option long_options[] = {
            { "help",   0, NULL, 'h' },
            { "config", 0, NULL, 'c' },
            { "log_config", 0, NULL, 'l' },
            { "debug",  0, NULL, 'd' },
            { NULL,     0, NULL, 'o' },
        };

        std::string config_file;
        std::string log_config_file;
        bool in_debug_mode = false;
        while (0 < (next_option = getopt_long(argc, argv, short_options, long_options, NULL))) {
            switch (next_option) {
                default:
                case 'h':
                    print_usage(argv[0]);
                    return 0;
                    break;
                case 'c':
                    config_file = optarg;
                    break;
                case 'l':
                    log_config_file = optarg;
                    break;
                case 'd':
                    in_debug_mode = true;
                    break;
            }
        }

        // initialize the log service
        {
            if (!LOG_SYS_INIT(log_config_file)) {
                return 1;
            }

            if (in_debug_mode) {
                LOG_SET_LEVEL(LOG_LEVEL_DEBUG);
            }
        }

        // config
        {
            LOG_INFO("Begin to cofig");

            StoreConf_SPtr conf(new StoreConf);
            if (!conf->parseConfig(config_file)) {
                LOG_ERROR("Failed to parse the config file: %s", config_file.c_str());
                goto __end;
            }

            // config metrics system
            {
                StoreConf_SPtr metrics_conf;
                if (conf->getStore(TXT_METRICS, metrics_conf)) {
                    MetricsSystem::getSingleton()->config(metrics_conf);
                }
                else {
                    LOG_INFO("No metrics sinks found");
                }
            }
        }

        MetricsSystem::getSingleton()->start();
        MetricsSystem::getSingleton()->stop();
    }
    catch(const std::exception& e) {
        LOG_ERROR("Exception in main: %s", e.what());
    }

__end:
    LOG_INFO("Exit now");
    return 0;
}
