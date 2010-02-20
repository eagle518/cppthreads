/*
 * Thread.cpp
 *
 *  Created on: May 7, 2009
 *      Author: Abd4llA
 */

#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include "Thread.h"
#include "CreationFailedException.h"
#include "AlreadyStartedException.h"
#include "AbnormalExitException.h"
#include "JoinFailedException.h"
#include "TimeOutException.h"
#include "PossibleDeadLockException.h"
#include "DetachException.h"
#include "ThreadingException.h"

using namespace std;

namespace cppthreads_starter_utils {
	extern "C"	void * init(void * args) {
		void ** argsArray = (void **)(args);
		cppthreads::Runnable *runnable = static_cast<cppthreads::Runnable *> (argsArray[0]);
		cppthreads::Thread *thread = static_cast<cppthreads::Thread *> (argsArray[1]);
		thread->running_ = true;
		try {
			// set thread's cancel state
			pthread_setcancelstate(thread->cancelable_, NULL);
			pthread_setcanceltype(thread->cancelType_, NULL);
			if (thread->cleanupHandler_ != NULL){
				// cleanup method
				pthread_cleanup_push(thread->cleanupHandler_, thread->cleanupArgs_);
				runnable->run();
				pthread_cleanup_pop(0);
			} else {
				runnable->run();
			}
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

	Thread::Thread(bool cancelable, CANCELATION_TYPE cancelType, bool detached) {
		init_(this, cancelable, cancelType, detached);
	}

	Thread::Thread(string name, bool cancelable, CANCELATION_TYPE cancelType, bool detached) : name_(name) {
		init_(this, cancelable, cancelType, detached);
	}

	Thread::Thread(Runnable *target, bool cancelable, CANCELATION_TYPE cancelType, bool detached) {
		init_(target, cancelable, cancelType, detached);
	}

	Thread::Thread(string name, Runnable *target, bool cancelable, CANCELATION_TYPE cancelType, bool detached) : name_(name){
		init_(target, cancelable, cancelType, detached);
	}

	void Thread::init_(Runnable *target, bool cancelable, CANCELATION_TYPE cancelType, bool detached) {
		lock_.lock();
		started_ = false;
		running_ = false;
		cleanupHandler_ = NULL;
		cleanupArgs_ = NULL;
		target_ = target;
		cancelable_ = cancelable;
		cancelType_ = cancelType;
		detached_ = detached;

		pthread_attr_init(&threadAttr_);
		pthread_cond_init(&threadTerminatedCond_, NULL);
		args_[0] = (void *)target_;
		args_[1] = (void *)this;
		pthread_attr_setdetachstate(&threadAttr_, detached ? PTHREAD_CREATE_DETACHED : PTHREAD_CREATE_JOINABLE);
		lock_.unlock();
	}

	void Thread::start() {
		lock_.lock();
		if (started_){
			lock_.unlock();
			throw AlreadyStartedException("Thread already started, can't run thread twice.", -1);
		}
		started_ = true;
		int32_t extCode = pthread_create(&threadHandle_, &threadAttr_,
								cppthreads_starter_utils::init, (void *)args_);

		lock_.unlock();
		if (extCode) {
			switch (errno) {
				case EAGAIN:
					throw CreationFailedException(
							"Thread creation failed due to lack of resources or due to some system limits",
							errno);
				case EINVAL:
					throw CreationFailedException(
							"Thread creation failed due to invalid attributes",
							errno);
				case EPERM:
					throw CreationFailedException(
							"You don't have enough permissions to set the required scheduling parameters or policy",
							errno);
				default: {
					throw CreationFailedException(
							"Unknown error occurred", errno);
				}
			}
		}
	}

	void Thread::run() {
		this->start();
	}

	void Thread::sleep(int millis) {
		usleep(millis* 1000);
	}

	void Thread::join() {
		lock_.lock();
		if (detached_){
			lock_.unlock();
			throw JoinFailedException("Can't join a detached thread",-1);
		}
		if (started_){
			int32_t extCode = pthread_join(threadHandle_, &returnResult_);
			lock_.unlock();
			if (extCode) {
				switch (errno){
					case EINVAL:
						throw JoinFailedException("Thread is not a joinable thread.", errno);
					case ESRCH:
						throw JoinFailedException("Can't find thread to join", errno);
					case EDEADLK:
						throw PossibleDeadLockException("Dead lock detected", errno);
					default :
						throw JoinFailedException("Unknown error occured", errno);
				}
			}
			else {
				if ((returnResult_)!= NULL){
					throw AbnormalExitException("Joined thread exited abnormally", -1);
				}
			}
		}
		else{
			lock_.unlock();
		}
	}

	void Thread::join(int timeout) {
		lock_.lock();
		if (detached_){
			lock_.unlock();
			throw JoinFailedException("Can't join a detached thread",-1);
		}

		if (clock_gettime(CLOCK_REALTIME, &currentTime_) == -1) {
			lock_.unlock();
			throw JoinFailedException("Cannot retrieve current time", -1);
			return;
		}
		currentTime_.tv_sec += timeout;
		if(started_ && running_){
			int32_t extCode = pthread_cond_timedwait(&threadTerminatedCond_, &(lock_.getMutexHandle()), &currentTime_);
			lock_.unlock();
			if (extCode){
				if (extCode == ETIMEDOUT){
					// timedwait timed out
					throw TimeOutException( "Timeout : Join timed out",	extCode);
				}
				else{
					switch(errno){
						case EINVAL:
							throw JoinFailedException(
									"Invalid mutix, condition or time",
									errno);
						case EPERM:
							throw JoinFailedException(
									"Invalid mutix: Mutix is not owned by current thread",
									errno);
						default:
							throw JoinFailedException(
									"Unknow error occured",
									extCode);
					}
				}

			} else {
				join();
			}
		} else if(started_) {
			lock_.unlock();
			join();
		} else {
			//Thread is not started, will unlock only
			lock_.unlock();
		}
	}

	void Thread::cancel(){
		pthread_cancel(threadHandle_);
		//maybe do some error handling
	}

	void Thread::kill(int signo){
		int32_t exitCode;
		exitCode = pthread_kill(threadHandle_, signo);

		if (exitCode != 0) {
			throw ThreadingException("Could not kill thread", exitCode);
		} 
	}

	void Thread::detach(){
		lock_.lock();
		if (detached_){
			lock_.unlock();
			throw DetachException("Thread is already detached", -1);
		}
		pthread_detach(threadHandle_);
		detached_ = true;
		lock_.unlock();
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

//	void Thread::setCancelationType(CANCELATION_TYPE type){
//		cancelType_ = type;
//		pthread_setcanceltype(type);
//	}

	int Thread::getId() const {
		return id_;
	}

	CANCELATION_TYPE Thread::getCancellationType(){
		return cancelType_;
	}

	void Thread::setCleanupHandler(void (*cleanupHandler)(void *), void *args){
		cleanupHandler_ = cleanupHandler;
		cleanupArgs_ = args;
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
		pthread_attr_destroy(&threadAttr_);
		delete target_;
	}

}
