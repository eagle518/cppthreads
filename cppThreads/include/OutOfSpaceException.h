/*
 * InvalidSemaphore.h
 *
 *  Created on: May 11, 2009
 *      Author: ahmed soliman
 */

#ifndef OUTOFSPACEEXCEPTION_H_
#define OUTOFSPACEEXCEPTION_H_
#include "ThreadingException.h"

namespace cppthreads {
	class OutOfSpaceException: ThreadingException {
		public:
			OutOfSpaceException(const char *message, int32_t errorCode) : ThreadingException(message, errorCode) {
			}
			virtual ~OutOfSpaceException(){};
	};
}

#endif /* OUTOFSPACEEXCEPTION_H_ */
