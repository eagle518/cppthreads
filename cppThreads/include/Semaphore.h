/*
 * Semaphore.h
 *
 *  Created on: May 5, 2009
 *      Author: ahmed soliman
 */

#ifndef SEMAPHORE_H_
#define SEMAPHORE_H_

#include "SuperObject.h"
#include <semaphore.h>
#include <limits.h>
namespace cppthreads {
	/**
	 * Semaphores are used to control access to a certain piece of code or object
	 */
	class Semaphore : public SuperObject{
		public:
			static const uint32_t MAX_VALUE = SEM_VALUE_MAX;
			Semaphore();
			Semaphore(uint32_t initValue);
			void signal();
			void wait();
			bool wait(uint32_t timeout);
			bool tryWait();
			uint32_t getValue();
			virtual ~Semaphore();

		private:
			sem_t semHandle_;
	};
}
#endif /* SEMAPHORE_H_ */
