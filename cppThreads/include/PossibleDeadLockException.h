/*
 * PossibleThreadDeadLockException.h
 *
 *  Created on: May 18, 2009
 *      Author: Abd4llA
 */

#ifndef POSSIBLETHREADDEADLOCKEXCEPTION_H_
#define POSSIBLETHREADDEADLOCKEXCEPTION_H_

#include<sys/types.h>

namespace cppthreads {
	class PossibleDeadLockException: public ThreadingException {
		public:
			PossibleDeadLockException(const char *msg, int32_t errorCode) : ThreadingException(msg,errorCode){

			}
			virtual ~PossibleDeadLockException() throw(){

			}
	};
}

#endif /* POSSIBLETHREADDEADLOCKEXCEPTION_H_ */
