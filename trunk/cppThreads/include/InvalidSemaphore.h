/*
 * InvalidSemaphore.h
 *
 *  Created on: May 6, 2009
 *      Author: ahmed soliman
 */

#ifndef INVALIDSEMAPHORE_H_
#define INVALIDSEMAPHORE_H_

#include "ThreadingException.h"
namespace cppthreads {
	class InvalidSemaphore : ThreadingException {
		public:
			InvalidSemaphore(const char *message, int32_t errorCode) : ThreadingException(message, errorCode) {}
	};
}

#endif /* INVALIDSEMAPHORE_H_ */
