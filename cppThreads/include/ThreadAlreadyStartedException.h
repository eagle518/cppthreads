/*
 * ThreadAlreadyStartedException.h
 *
 *  Created on: May 17, 2009
 *      Author: Abd4llA
 */

#ifndef THREADALREADYSTARTEDEXCEPTION_H_
#define THREADALREADYSTARTEDEXCEPTION_H_
#include <sys/types.h>
#include "ThreadingException.h"

namespace cppthreads{
	class ThreadAlreadyStartedException : public ThreadingException {
		public:
			ThreadAlreadyStartedException(const char *msg, int32_t errorCode) : ThreadingException(msg,errorCode){

			}
			virtual ~ThreadAlreadyStartedException(){

			}
	};

}

#endif /* THREADALREADYSTARTEDEXCEPTION_H_ */
