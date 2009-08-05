#include <errno.h>
#include <unistd.h>
#include "Condition.h"
#include "InterruptedException.h"
#include "ThreadingException.h"

extern int errno;

namespace cppthreads {
	Condition::Condition(Mutex& mutex) : mutex_(mutex) {
		pthread_cond_init(&conditionHandle_, NULL);
	}

	void Condition::await() {
		mutex_.lock();
		pthread_mutex_t handle = mutex_.getMutexHandle();
		
		if (pthread_cond_wait(&conditionHandle_, &handle) != 0) {
			mutex_.unlock();
			perror("Condition::await()");
			throw InterruptedException("Waiting on condition failed!", errno);
		}

		mutex_.unlock();
	}

	bool Condition::await(uint32_t timeOut) {
		bool returnCode = false;
        	struct timespec timeOutStructure;
		pthread_mutex_t handle = mutex_.getMutexHandle();

        	if(clock_gettime(CLOCK_REALTIME, &timeOutStructure) == -1)
                	perror("Condition::await():");

        	timeOutStructure.tv_sec += timeOut;

        	mutex_.lock();
        	int32_t ret = pthread_cond_timedwait(&conditionHandle_, &handle, &timeOutStructure);
        	if (ret != 0) {
                	perror("Condition::await():");
                	if (ret == ETIMEDOUT) {
                        	returnCode = true;
                	} else {
                        	mutex_.unlock();
                        	throw cppthreads::InterruptedException("Conditional wait on Object Failed!" , errno);
                	}
        	}
        	mutex_.unlock();

        	return returnCode;

	}

	void Condition::signal() {
		if (pthread_cond_signal(&conditionHandle_) != 0) {
			perror("Condition::signal()");
			throw ThreadingException("Failed to signal on condition", errno);
		}
	}

	void Condition::signalAll() {
		if (pthread_cond_broadcast(&conditionHandle_) != 0) {
			perror("Condition::signalAll()");
			throw ThreadingException("Failed to signal all threads waiting on confition", errno);
		}
	}

	Condition::~Condition() {
		pthread_cond_destroy(&conditionHandle_);
	}
}
