/*
 * Thread.h
 *
 *  Created on: May 5, 2009
 *      Author: Abd4llA
 */

#ifndef THREAD_H_
#define THREAD_H_
#include "Runnable.h"
#include <iostream>

/**
 * Thread states that represents its life cycle.
 * The thread state goes over many changes throughout its life, this Enum represents those states.
 * NEW : Thread has not yet started.
 * RUNNABLE: Thread is in the queue ready and waiting to take its turn to run.
 * BLOCKED: Thread is blocked on a some object lock.
 * WAITING: Thread is waiting indefinitely for another thread to perform a particular action
 * TIMED_WAITING: Thread is waiting indefinitely for another thread to perform an action up to a specific time
 * TERMINATED: Thread finished running
 */
static enum State {

	/**
	 *Thread has not yet started.
	 */
	NEW,
	/**
	 * Thread is in the queue ready and waiting to take its turn to run.
	 */
	RUNNABLE,
	/**
	 * Thread is blocked on a some object lock.
	 */
	BLOCKED,
	/**
	 * Thread is waiting indefinitely for another thread to perform a particular action
	 */
	WAITING,
	/**
	 * Thread is waiting indefinitely for another thread to perform an action up to a specific time
	 */
	TIMED_WAITING,
	/**
	 * Thread finished running
	 */
	TERMINATED
};

/**
 *
 */
class Thread: Runnable {
private:
	/**
	 * Current thread state
	 */
	State state;
	/**
	 * Thread priority
	 */
	int priority;
	/**
	 * Unique thread ID
	 */
	int id;

	String name;
	/**
	 * Our runnable object, it should be passed in the constructor
	 */
	Runnable target;
public:
	Thread();
	Thread(Runnable target);
	Thread(String name);
	Thread(Runnable target, String name);
	void start();
	void run();
	void join();
	void join(int millis);
	State getState() const
    {
		return state;
    }

    int getPriority() const
    {
        return priority;
    }

    void setPriority(int priority);

    int getId() const
    {
        return id;
    }

    String getName() const
    {
        return name;
    }

    void setName(String name)
    {
        this->name = name;
    }

};

#endif /* THREAD_H_ */
