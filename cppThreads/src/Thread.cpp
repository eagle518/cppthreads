/*
 * Thread.cpp
 *
 *  Created on: May 7, 2009
 *      Author: Abd4llA
 */

#include <pthread.h>
#include <errno.h>
#include "Thread.h"
#include "ThreadCreationFailedException.h"
using namespace std;

namespace cppthreads_starter_utils {
	void * init(void * runnable) {
		cppthreads::Runnable *thread =
				static_cast<cppthreads::Runnable *> (runnable);
		thread->running_ = true;
		try {
			thread->run();
		} catch (...) {
			thread->running_ = false;
			throw ;
		}
		thread->running_ = false;
		pthread_exit(NULL);
	}
}

namespace cppthreads {

	Thread::Thread() : target_(this){

	}
	Thread::Thread(string name) : name_(name), target_(this){

	}

	Thread::Thread(Runnable *target) : target_(target) {

	}

	Thread::Thread(Runnable *target, string name) : target_(target), name_(name){

	}

	void Thread::start() {
		int32_t extCode = pthread_create(&threadHandle_, NULL,
								cppthreads_starter_utils::init, (void *) target_);
		if (extCode) {
			switch (errno) {
				case EAGAIN:
					throw new ThreadCreationFailedException(
							"Thread creation failed due to lack of resources or due to some system limits",
							errno);
				case EINVAL:
					throw new ThreadCreationFailedException(
							"Thread creation failed due to invalid attributes",
							errno);
				case EPERM:
					throw new ThreadCreationFailedException(
							"You don't have enough permissions to set the required scheduling parameters or policy",
							errno);
				default: {
					throw new ThreadCreationFailedException(
							"Unknown error occurred", errno);
				}
			}
		}
	}
	/**
	 * The entry method of the new thread. This method will run in a new thread
	 * Override this method and put the code which you want to run in a new thread inside.
	 */
	void Thread::run() {

	}
	/**
	 * Puts thread to sleep for "millis" seconds
	 */
	void Thread::sleep(int millis) {

	}
	/**
	 * Wait until this thread finish execution.
	 * Thread calling this join() will block until this Thread finishes execution
	 */
	void Thread::join() {
		pthread_join(threadHandle_, &returnResult_);
	}
	/**
	 * Wait until thread finish execution up to timeout which is expressed in millis
	 */
	void Thread::join(int timeout) {
	}

	void Thread::yield(){

	}
	int Thread::getPriority() const {
		return priority_;
	}

	void Thread::setPriority(int priority) {
		priority_ = priority;
	}

	int Thread::getId() const {
		return id_;
	}

	string Thread::getName() const {
		return name_;
	}

	void Thread::setName(string name) {
		name_ = name;
	}

	bool Thread::isRunning() {
		return target_->isRunning();
	}

	Thread::~Thread() {
		// TODO Auto-generated destructor stub
		delete target_;
	}

}
