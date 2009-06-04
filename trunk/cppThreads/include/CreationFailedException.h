/*
 * ThreadCreationFailedException.h
 *
 *  Created on: May 13, 2009
 *      Author: Abd4llA
 */

#ifndef THREADCREATIONFAILEDEXCEPTION_H_
#define THREADCREATIONFAILEDEXCEPTION_H_

#include "ThreadingException.h"
#include <sys/types.h>
namespace cppthreads {
	class CreationFailedException: public ThreadingException {
		private:

		public:
			CreationFailedException(const char *message, int32_t errCode) : ThreadingException(message,errCode){

			}
			virtual ~CreationFailedException() throw(){

			}

	};
}

#endif /* THREADCREATIONFAILEDEXCEPTION_H_ */
