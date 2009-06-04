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
	class AlreadyStartedException : public ThreadingException {
		public:
			AlreadyStartedException(const char *msg, int32_t errorCode) : ThreadingException(msg,errorCode){

			}
			virtual ~AlreadyStartedException() throw(){

			}
	};

}

#endif /* THREADALREADYSTARTEDEXCEPTION_H_ */
