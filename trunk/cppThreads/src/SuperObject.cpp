#include "SuperObject.h"
#include "InterruptedException.h"
#include "ThreadingException.h"
#include <iostream>
#include <unistd.h>
#include <errno.h>

extern int errno;

SuperObject::SuperObject() {
	pthread_mutex_init(&globalMutexHandle_, NULL);
	pthread_cond_init(&condHandle_, NULL);
}

void SuperObject::wait() {
	if(pthread_cond_wait(&condHandle_, &globalMutexHandle_) != 0)
		throw cppthreads::InterruptedException("Waiting on Object Failed!", errno);
}

bool SuperObject::wait(uint32_t timeOut) {
	struct timespec timeOutStructure;

	if(clock_gettime(CLOCK_REALTIME, &timeOutStructure) == -1)
		perror("wait():");
	
	timeOutStructure.tv_sec += timeOut;

	int32_t ret = pthread_cond_timedwait(&condHandle_, &globalMutexHandle_, &timeOutStructure);
	if (ret != 0) {
		perror("wait():");
		if (ret == ETIMEDOUT)
			return false;

		throw cppthreads::InterruptedException("Timed wait on Object Failed!" , errno);
	}

	return true;
}

void SuperObject::notify() {
	if(pthread_cond_signal(&condHandle_) != 0) {
		perror("notify():");
		throw cppthreads::ThreadingException("Failed to notify on object", errno);
	}
}

void SuperObject::notifyAll() {
	if(pthread_cond_broadcast(&condHandle_) != 0) {
		perror("notifyAll():");
		throw cppthreads::ThreadingException("Failed to notifyAll threads waiting on Object", errno);
	}
}

SuperObject::~SuperObject() {
	pthread_mutex_destroy(&globalMutexHandle_);
	pthread_cond_destroy(&condHandle_);
}
