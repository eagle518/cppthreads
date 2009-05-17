/*
 * ThreadJoiningFailedException.h
 *
 *  Created on: May 18, 2009
 *      Author: Abd4llA
 */

#ifndef THREADJOININGFAILEDEXCEPTION_H_
#define THREADJOININGFAILEDEXCEPTION_H_

#include<sys/types.h>

namespace cppthreads {
	class ThreadJoiningFailedException: public ThreadingException {
		public:
			ThreadJoiningFailedException(const char *msg, int32_t errorCode) : ThreadingException(msg,errorCode){

			}
			virtual ~ThreadJoiningFailedException(){

			}
	};
}
#endif /* THREADJOININGFAILEDEXCEPTION_H_ */
