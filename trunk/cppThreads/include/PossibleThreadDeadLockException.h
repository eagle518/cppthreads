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
	class PossibleThreadDeadLockException: public ThreadingException {
		public:
			PossibleThreadDeadLockException(const char *msg, int32_t errorCode) : ThreadingException(msg,errorCode){

			}
			virtual ~PossibleThreadDeadLockException(){

			}
	};
}

#endif /* POSSIBLETHREADDEADLOCKEXCEPTION_H_ */
