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
	extern "C"	void * init(void * args) {
		void ** argsArray = (void **)(args);
		cppthreads::Runnable *runnable = static_cast<cppthreads::Runnable *> (argsArray[0]);
		cppthreads::Thread *thread = static_cast<cppthreads::Thread *> (argsArray[1]);
		thread->running_ = true;
		try {
			runnable->run();
			thread->running_ = false;
		 }
		catch (...) {
			thread->running_ = false;
		}
			pthread_cond_broadcast( &(thread->threadTerminatedCond_) );
			pthread_exit(NULL);
	}
}

namespace cppthreads {

	Thread::Thread() :
		started_(false), target_(this), running_(false) {
		init_();
	}

	Thread::Thread(string name) :
		started_(false), name_(name), target_(this), running_(false) {
		init_();
	}

	Thread::Thread(Runnable *target) :
		started_(false), target_(target), running_(false) {
		init_();
	}

	Thread::Thread(Runnable *target, string name) :
		started_(false),target_(target), name_(name), running_(false) {
		init_();
	}

	void Thread::init_() {
		pthread_cond_init(&threadTerminatedCond_, NULL);
		args_[0] = (void *)target_;
		args_[1] = (void *)this;
	}

	void Thread::start() {
		lock_.lock();
		if (started_){
			lock_.unlock();
			throw ThreadAlreadyStartedException("Thread already started, can't run thread twice.", -1);
		}
		started_ = true;
		int32_t extCode = pthread_create(&threadHandle_, NULL,
								cppthreads_starter_utils::init, (void *)args_);
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

	void Thread::run() {

	}

	void Thread::sleep(int millis) {
		usleep(millis* 1000);
	}

	void Thread::join() {
		lock_.lock();
		int32_t extCode = pthread_join(threadHandle_, &returnResult_);
		lock_.unlock();
		if (extCode) {
			switch (errno){
				case EINVAL:
					throw ThreadJoiningFailedException("Thread is not a joinable thread.", errno);
				case ESRCH:
					throw ThreadJoiningFailedException("Can't find thread to join", errno);
				case EDEADLK:
					throw PossibleThreadDeadLockException("Dead lock detected", errno);
				default :
					throw ThreadJoiningFailedException("Unknown error occured", errno);
			}
		}
		else {
			if ((returnResult_)!= NULL){
				throw JoinedThreadAbnormalExitException("Joined thread exited abnormally", -1);
			}
		}
	}

	void Thread::join(int timeout) {
		lock_.lock();
		struct timespec currentTime;
		if (clock_gettime(CLOCK_REALTIME, &currentTime) == -1) {
			lock_.unlock();
			throw ThreadJoiningFailedException("Cannot retrieve current time", -1);
			return;
		}
		currentTime.tv_sec += timeout;
		if(started_ && running_){
			int32_t ret = pthread_cond_timedwait(&threadTerminatedCond_, &(lock_.getMutexHandle()), &currentTime);
			lock_.unlock();
			if (ret){
				switch(errno){
					case ETIMEDOUT:
						throw ThreadJoiningFailedException(
								"Timeout Error: The time you specified already passed",
								errno);
					case EINVAL:
						throw ThreadJoiningFailedException(
								"Invalid mutix, condition or time",
								errno);
					case EPERM:
						throw ThreadJoiningFailedException(
								"Invalid mutix: Mutix is not owned by current thread",
								errno);
					default:
						throw ThreadJoiningFailedException(
								"Unknow error occured",
								errno);
				}

			} else {
				join();
			}
		} else if(started_) {
			lock_.unlock();
			join();
		} else {
			//TODO: Check what should happen
			cout << "Thread::Join: Thread is not running!" << endl;
			lock_.unlock();

		}
	}

	void Thread::yield() {
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
		lock_.lock();
		bool ret = running_;
		lock_.unlock();
		return ret;
	}

	Thread::~Thread() {
		pthread_cond_destroy(&threadTerminatedCond_);
		delete target_;
	}

}
