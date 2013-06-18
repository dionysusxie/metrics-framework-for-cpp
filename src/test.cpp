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
#include <signal.h>
#include "test.h"
#include "MetricsSystem.h"

using namespace std;
using namespace boost;
using namespace gmf;

const string DEFAULT_CONFIG_FILE("/etc/test/test.conf");
const string TXT_METRICS = "metrics";


//////////////////////////////////////////////////////////////////////////////////////////
//
// class Ctrl_C:
//

shared_ptr<Ctrl_C> Ctrl_C::s_pSingleton;

shared_ptr<Ctrl_C> Ctrl_C::getSingleton() {
    if (Ctrl_C::s_pSingleton.get() == NULL) {
        Ctrl_C::s_pSingleton.reset(new Ctrl_C());
    }

    return Ctrl_C::s_pSingleton;
}

void Ctrl_C::sigHandler(int sig_num) {
    if (SIGINT == sig_num) {
        Ctrl_C::getSingleton()->pressCtrlC();
    }
}

Ctrl_C::Ctrl_C():
        exit_now_(false) {
    signal(SIGINT, Ctrl_C::sigHandler);
}

Ctrl_C::~Ctrl_C() {
}

void Ctrl_C::run() {
    bool run = true;

    while (run) {
        sleep(1);

        // we should exit now?
        {
            boost::lock_guard<mutex> lock(this->mutex_);
            if (exit_now_) {
                run = false;
            }
        }
    }

    cerr << "Exit now!" << endl;
}

void Ctrl_C::pressCtrlC() {
    boost::lock_guard<mutex> lock(this->mutex_);
    exit_now_ = true;
    cerr << "\nCtrl + C is pressed!" << endl;
}


//////////////////////////////////////////////////////////////////////////////////////////
//
// main()
//

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

            // parse the config file
            StoreConf_SPtr conf(new StoreConf);
            if (!conf->parseConfig(config_file)) {
                LOG_ERROR("Failed to parse the config file: %s", config_file.c_str());
                goto __end;
            }

            // config metrics system
            {
                StoreConf_SPtr metrics_conf;
                if (conf->getStore(TXT_METRICS, metrics_conf)) {
                    if (!MetricsSystem::getSingleton()->config(metrics_conf)) {
                        LOG_ERROR("Failed to config Metrics System!");
                        goto __end;
                    }
                }
                else {
                    LOG_ERROR("No config items for Metrics System!");
                    goto __end;
                }
            }
        }

        // run until the user interrupt it by pressing Ctrl + C
        Ctrl_C::getSingleton()->run();

        // close the Metrics System before exiting
        MetricsSystem::getSingleton()->stop();
    }
    catch(const std::exception& e) {
        LOG_ERROR("Exception in main: %s", e.what());
    }

__end:
    LOG_INFO("Exit");
    return 0;
}
