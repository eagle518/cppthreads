	/*
 * ThreadingException.h
 *
 *  Created on: May 6, 2009
 *      Author: ahmed soliman
 */

#ifndef THREADINGEXCEPTION_H_
#define THREADINGEXCEPTION_H_
#include "SuperObject.h"
#include <string.h>
#include <string>
#include <exception>
#include <iostream>
using namespace std;

namespace cppthreads {
	class ThreadingException : public SuperObject , public std::exception{
		public:
			ThreadingException(const char *message, int32_t errorCode) : message_(message), errorCode_(errorCode) {
				if (errorCode != NULL){
					formattedMsg_ << message << "\nErrorCode: " << errorCode << endl;
				}
				else
					formattedMsg_ << message;
			}

			ThreadingException(const ThreadingException & exception){

			}

			virtual int32_t getErrorCode() {
				return errorCode_;
			}

			virtual const char* what() const throw() {
				//TODO: change the new to some better impl.
				return (new string(formattedMsg_.str()))->c_str();
			}

			virtual ~ThreadingException() throw() {}

		private:
			const char *message_;
//			char formattedMsg_[100];
			stringstream formattedMsg_;
			int32_t errorCode_;
	};
}


#endif /* THREADINGEXCEPTION_H_ */
