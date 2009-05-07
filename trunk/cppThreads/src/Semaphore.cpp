/*
 * Semaphore.cpp
 *
 *  Created on: May 5, 2009
 *      Author: ahmed soliman
 */

#include <time.h>
#include <errno.h>
#include <iostream>
#include "Semaphore.h"
#include "InvalidSemaphore.h"
#include "InterruptedException.h"

namespace cppthreads {
	Semaphore::Semaphore() {
		sem_init(&semHandle_, 0, 0);
	}

	Semaphore::Semaphore(int32_t initValue) {
		sem_init(&semHandle_, 0, initValue);
	}

	int32_t Semaphore::getValue() {
		int32_t currentValue = 0;
		int32_t res = sem_getvalue(&semHandle_, &currentValue);
		if (res != 0) {
			// Throw an exception
			// we don't need to read errno here because only one type of errors can happen
			// that is the semaphore is not valid
			throw InvalidSemaphore("The Semaphore you are trying to use is not a valid semaphore.", res);
		}
		return currentValue;
	}
	/**
	 * Increments (unlocks) the semaphore, if the semaphore is increased of a zero value, any waiting thread (blocking on wait())
	 * will be unlocked and will decrease the lock, note that this call is atomic so you don't have to worry about several threads
	 * calling post() and wait()
	 */
	void Semaphore::post() {
		int32_t res = sem_post(&semHandle_);
		if (res != 0) {
			throw InvalidSemaphore("Cannot increase an invalid semaphore", res);
		}
	}
	/**
	 * Decrement (locks) the semnote that this call is atomic so you don't have to worry about several threads
	 * calling post() and wait()aphore, if the semaphore value is already larger than 0 the call will return immediately and the semaphore
	 * will decreas. If the value is already zero the call will block until we can do the decrement (somebody else calls post)
	 * note that this call is atomic so you don't have to worry about several threads
	 * calling post() and wait()
	 */
	void Semaphore::wait() {
		int res = sem_wait(&semHandle_);
		if (res != 0) {
			switch (errno) {
				case EINTR:
					throw InterruptedException("wait() was interrupted by a signal", errno);
				case EINVAL:
					throw InvalidSemaphore("Cannot decrement invalid semaphoer", errno);
					break;
				default:
					throw ThreadingException("Unknown Exception in wait()", errno);
			}
		}
	}

	bool Semaphore::wait(int32_t timeout) {
		struct timespec timeoutStructure;
		bool ret = false;
		if (clock_gettime(CLOCK_REALTIME, &timeoutStructure) == -1) {
			// ERROR
			std::cerr << "Couldn't get the current time" << std::endl;
		}

		timeoutStructure.tv_sec += timeout;
		int32_t res = sem_timedwait(&semHandle_, &timeoutStructure);
		if (res == 0) {
			ret = true;
		} else {
			switch (errno) {
				case EINTR:
					throw InterruptedException("wait() was interrupted by a signal", errno);
				case EINVAL:
					throw InvalidSemaphore("Cannot decrement invalid semaphoer", errno);
					break;
				case ETIMEDOUT:
					ret = false;
					break;
				default:
					throw ThreadingException("Unknown Exception in wait()", errno);
			}
		}
		return ret;

	}
	/**
	 * Try to wait will work exactly like wait but will not block if the semaphore is not ready for decrement, it'll simply return
	 * false instead, then you know the the semaphore is not ready for decrement and if you called wait() at then you'll be locked!
	 */
	bool Semaphore::tryWait() {
		bool ret = false;
		int32_t res = sem_trywait(&semHandle_);
		if (res == 0) {
			ret = true;
		}
		return ret;

	}

	Semaphore::~Semaphore() {
		sem_destroy(&semHandle_);
	}
}
