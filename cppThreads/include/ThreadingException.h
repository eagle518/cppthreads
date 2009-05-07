/*
 * ThreadingException.h
 *
 *  Created on: May 6, 2009
 *      Author: ahmed soliman
 */

#ifndef THREADINGEXCEPTION_H_
#define THREADINGEXCEPTION_H_
#include "SuperObject.h"

namespace cppthreads {
	class ThreadingException : public SuperObject{
		public:
			ThreadingException(const char *message, int32_t errorCode) : message_(message), errorCode_(errorCode){

			}
			virtual const char *getMessage() {
				return message_;
			}
			virtual int32_t getErrorCode() {
				return errorCode_;
			}
			virtual ~ThreadingException() {}
		private:
			const char *message_;
			int32_t errorCode_;
	};
}


#endif /* THREADINGEXCEPTION_H_ */
