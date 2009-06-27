/*
 * ThreadJoiningFailedException.h
 *
 *  Created on: May 18, 2009
 *      Author: Abd4llA
 */

#ifndef TIMEOUTEXCEPTION_H_
#define TIMEOUTEXCEPTION_H_

#include<stdint.h>

namespace cppthreads {
	class TimeOutException: public ThreadingException {
		public:
			TimeOutException(const char *msg, int32_t errorCode) : ThreadingException(msg,errorCode){

			}
			virtual ~TimeOutException() throw(){

			}
	};
}
#endif /* TIMEOUTEXCEPTION_H_ */
