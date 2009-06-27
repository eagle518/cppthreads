/*
 * DetachException.h
 *
 *  Created on: May 18, 2009
 *      Author: Abd4llA
 */

#ifndef DETACHEXCEPTION_H_
#define DETACHEXCEPTION_H_

#include<stdint.h>

namespace cppthreads {
	class DetachException: public ThreadingException {
		public:
			DetachException(const char *msg, int32_t errorCode) : ThreadingException(msg,errorCode){

			}
			virtual ~DetachException() throw(){

			}
	};
}


#endif /* DETACHEXCEPTION_H_ */
