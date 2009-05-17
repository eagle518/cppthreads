/*
 * JoinedThreadAbnormalExitException.h
 *
 *  Created on: May 18, 2009
 *      Author: Abd4llA
 */

#ifndef JOINEDTHREADABNORMALEXITEXCEPTION_H_
#define JOINEDTHREADABNORMALEXITEXCEPTION_H_

#include<sys/types.h>

namespace cppthreads {
	class JoinedThreadAbnormalExitException: public ThreadingException {
		public:
			JoinedThreadAbnormalExitException(const char *msg, int32_t errorCode) : ThreadingException(msg,errorCode){

			}
			virtual ~JoinedThreadAbnormalExitException(){

			}
	};
}


#endif /* JOINEDTHREADABNORMALEXITEXCEPTION_H_ */
