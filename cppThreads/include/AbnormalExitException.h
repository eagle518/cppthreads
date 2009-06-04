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
	class AbnormalExitException: public ThreadingException {
		public:
			AbnormalExitException(const char *msg, int32_t errorCode) : ThreadingException(msg,errorCode){

			}
			virtual ~AbnormalExitException() throw(){

			}
	};
}


#endif /* JOINEDTHREADABNORMALEXITEXCEPTION_H_ */
