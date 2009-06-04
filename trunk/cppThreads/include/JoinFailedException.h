/*
 * ThreadJoiningFailedException.h
 *
 *  Created on: May 18, 2009
 *      Author: Abd4llA
 */

#ifndef JOINFAILEDEXCEPTION_H_
#define JOINFAILEDEXCEPTION_H_

#include<sys/types.h>

namespace cppthreads {
	class JoinFailedException: public ThreadingException {
		public:
			JoinFailedException(const char *msg, int32_t errorCode) : ThreadingException(msg,errorCode){

			}
			virtual ~JoinFailedException() throw(){

			}
	};
}
#endif /* JOINFAILEDEXCEPTION_H_ */
