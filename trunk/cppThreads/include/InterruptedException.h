/*
 * InvalidSemaphore.h
 *
 *  Created on: May 7, 2009
 *      Author: ahmed soliman
 */

#ifndef INTERRUPTEDEXCEPTION_H_
#define INTERRUPTEDEXCEPTION_H_
#include "ThreadingException.h"

namespace cppthreads {
	class InterruptedException: ThreadingException {
		public:
			InterruptedException(const char *message, int32_t errorCode) : ThreadingException(message, errorCode) {
			}
			virtual ~InterruptedException() throw(){};
	};
}

#endif /* INTERRUPTEDEXCEPTION_H_ */
