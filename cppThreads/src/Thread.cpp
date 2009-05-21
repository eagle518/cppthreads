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
#include "ThreadAlreadyStartedException.h"
#include "JoinedThreadAbnormalExitException.h"
#include "ThreadJoiningFailedException.h"
#include "PossibleThreadDeadLockException.h"

using namespace std;

namespace cppthreads_starter_utils {
	void * init(void * runnable) {
		cppthreads::Runnable *thread =
				static_cast<cppthreads::Runnable *> (runnable);
		thread->running_ = true;
		try {
			thread->run();
			thread->running_ = false;
			pthread_exit(NULL);
		} catch (...) {
			thread->running_ = false;
			throw;
		}
	}
}

namespace cppthreads {

	Thread::Thread() : started_(false),target_(this){}
	Thread::Thread(string name) : started_(false),name_(name), target_(this){}
	Thread::Thread(Runnable *target) : started_(false),target_(target) {}
	Thread::Thread(Runnable *target, string name) : started_(false),target_(target), name_(name){}

	void Thread::start() {
		lock_.lock();
		if (started_){
			lock_.unlock();
			throw ThreadAlreadyStartedException("Thread already started, can't run thread twice.",-1);
		}
		started_ = true;
		int32_t extCode = pthread_create(&threadHandle_, NULL,
								cppthreads_starter_utils::init, (void *) target_);
		lock_.unlock();
		if (extCode) {
			switch (errno) {
				case EAGAIN:
					throw ThreadCreationFailedException(
							"Thread creation failed due to lack of resources or due to some system limits",
							errno);
				case EINVAL:
					throw ThreadCreationFailedException(
							"Thread creation failed due to invalid attributes",
							errno);
				case EPERM:
					throw ThreadCreationFailedException(
							"You don't have enough permissions to set the required scheduling parameters or policy",
							errno);
				default: {
					throw ThreadCreationFailedException(
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
		lock_.lock();
		int32_t extCode = pthread_join(threadHandle_, &returnResult_);
		lock_.unlock();
		if (extCode) {
			switch (errno){
				case EINVAL:
					throw ThreadJoiningFailedException("Thread is not a joinable thread.",errno);
				case ESRCH:
					throw ThreadJoiningFailedException("Can't find thread to join",errno);
				case EDEADLK:
					throw PossibleThreadDeadLockException("Dead lock detected",errno);
				default :
					throw ThreadJoiningFailedException("Unknown error occured",errno);
			}
		}
		else {
			if ((returnResult_)!= NULL){
				throw JoinedThreadAbnormalExitException("Joined thread exited abnormally",-1);
			}
		}
	}
	/**
	 * Wait until thread finish execution up to timeout which is expressed in millis
	 */
	void Thread::join(int timeout) {
	}

	void Thread::yield(){
		lock_.lock();
		pthread_yield();
		lock_.unlock();
	}
	int Thread::getPriority() const {
		return priority_;
	}

	void Thread::setPriority(int priority) {
		lock_.lock();
		priority_ = priority;
		lock_.unlock();
	}

	int Thread::getId() const {
		return id_;
	}

	string Thread::getName() const {
		return name_;
	}

	void Thread::setName(string name) {
		lock_.lock();
		name_ = name;
		lock_.unlock();
	}

	bool Thread::isRunning() {
		return target_->isRunning();
	}

	Thread::~Thread() {
		// TODO Throw exception if we are deleting a running thread
		delete target_;
	}

}
