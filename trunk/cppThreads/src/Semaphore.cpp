/*
 * Semaphore.cpp
 *
 *  Created on: May 5, 2009
 *      Author: ahmed soliman
 */

#include "Semaphore.h"
#include "InvalidSemaphore.h"
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
	void Semaphore::post() {

	}
	void Semaphore::wait() {

	}
	Semaphore::~Semaphore() {
		sem_destroy(&semHandle_);
	}
}
