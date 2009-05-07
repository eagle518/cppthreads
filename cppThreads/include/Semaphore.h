/*
 * Semaphore.h
 *
 *  Created on: May 5, 2009
 *      Author: ahmed soliman
 */

#ifndef SEMAPHORE_H_
#define SEMAPHORE_H_

#include <semaphore.h>

namespace cppthreads {
	/**
	 * Semaphores are used to control access to a certain piece of code or object
	 */
	class Semaphore {
		public:
			Semaphore();
			Semaphore(int32_t initValue);
			void post();
			void wait();
			bool wait(int32_t timeout);
			bool tryWait();
			int32_t getValue();
			virtual ~Semaphore();

		private:
			sem_t semHandle_;
	};
}
#endif /* SEMAPHORE_H_ */
