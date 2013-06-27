/*
 * sample.h
 *
 *  Created on: Jun 18, 2013
 *      Author: xieliang
 */

#ifndef SAMPLE_H_
#define SAMPLE_H_

#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>


// press Ctrl + C to exit the app
class Ctrl_C {
public:
    typedef void (*CallbackFunc)();
public:
    static boost::shared_ptr<Ctrl_C> getSingleton();
    static void sigHandler(int);

public:
    virtual ~Ctrl_C();

public:
    void registerCallback(CallbackFunc fn);
    void run();

private:
    Ctrl_C();
    void pressCtrlC();

private:
    static boost::shared_ptr<Ctrl_C> s_pSingleton;

private:
    bool exit_now_;
    boost::mutex exit_mutex_;

    CallbackFunc func_;
};


#endif /* SAMPLE_H_ */
