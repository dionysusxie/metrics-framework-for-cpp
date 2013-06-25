/*
 * test.h
 *
 *  Created on: Jun 18, 2013
 *      Author: xieliang
 */

#ifndef TEST_H_
#define TEST_H_

#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>


// press Ctrl + C to exit the app
class Ctrl_C {
public:
    typedef void (*Function)();
public:
    static boost::shared_ptr<Ctrl_C> getSingleton();
    static void sigHandler(int);

public:
    virtual ~Ctrl_C();

public:
    void registerFunc(Function fn);
    void run();

private:
    Ctrl_C();
    void pressCtrlC();

private:
    static boost::shared_ptr<Ctrl_C> s_pSingleton;

private:
    bool exit_now_;
    boost::mutex exit_mutex_;

    Function func_;
};


#endif /* TEST_H_ */
