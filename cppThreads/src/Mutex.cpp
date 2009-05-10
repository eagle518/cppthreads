/*
 * Mutex.cpp
 *
 *  Created on: May 5, 2009
 *      Author: ahmed soliman
 */

#include "Mutex.h"
#include "InvalidMutex.h"
#include <iostream>
#include <errno.h>

namespace cppthreads {
	Mutex::Mutex() :
		locked_(false) {
		pthread_mutex_init(&mutexHandle_, NULL);

	}

	void Mutex::lock() {
		pthread_mutex_lock(&mutexHandle_);
		locked_ = true;
	}

	bool Mutex::lock(uint32_t timeout) {
		struct timespec timeoutStructure;
		bool ret = false;
		if (clock_gettime(CLOCK_REALTIME, &timeoutStructure) == -1) {
			// ERROR
			std::cerr << "Couldn't get the current time" << std::endl;
		}

		timeoutStructure.tv_sec += timeout;

		int32_t res = pthread_mutex_timedlock(&mutexHandle_, &timeoutStructure);
		if (res == 0) {
			locked_ = true;
			ret = true;
		} else {
			switch (res) {
				case EINVAL:
					throw InvalidMutex("Cannot lock uninitialized mutex", res);
					break;
				case EAGAIN:
					throw ThreadingException("Mutex couldn't be acquired because the maximum number of recursive locks for mutex has been exceeded.", res);
				case ETIMEDOUT:
					return false;
					break;
				default:
					throw ThreadingException("Unknown Exception in wait()", res);
			}
		}
		return ret;
	}
	bool Mutex::isLocked() {
		return locked_;
	}
	bool Mutex::tryLock() {
		if (pthread_mutex_trylock(&mutexHandle_) == 0) {
			locked_ = true;
			return true;
		}
		return false;
	}

	void Mutex::unlock() {
		if (locked_) {
			locked_ = false;
			pthread_mutex_unlock(&mutexHandle_);
		}
	}

	bool Mutex::tryUnlock() {
		//pthread_mutex_tryunlock(&mutexHandle_);
	}

	Mutex::~Mutex() {
		if (locked_) {
			unlock();
		}
		pthread_mutex_destroy(&mutexHandle_);
	}
}
