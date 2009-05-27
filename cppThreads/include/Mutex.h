/*
 * Mutex.h
 *
 *  Created on: May 5, 2009
 *      Author: ahmed soliman
 */

#ifndef MUTEX_H_
#define MUTEX_H_
#include "SuperObject.h"
#include "pthread.h"
#include <iostream>
namespace cppthreads {
	/**
	 * Initial support only supports NORMAL mutex, not ERROR_CHECK, so there is no deadlock detection for this version.
	 */
	class Mutex: public SuperObject {
		public:
			Mutex();
			virtual void lock();
			virtual bool lock(uint32_t timeout);
			virtual bool tryLock();
			virtual bool isLocked();
			virtual pthread_mutex_t getMutexHandle();
			virtual void unlock();
			virtual bool tryUnlock();

			virtual ~Mutex();
		protected:
			pthread_mutex_t mutexHandle_;
			bool locked_;

	};
}
#endif /* MUTEX_H_ */
