/*
 * Thread.h
 *
 *  Created on: May 5, 2009
 *      Author: Abd4llA
 */

#ifndef RUNNABLE_H_
#define RUNNABLE_H_

#include <iostream>
#include "SuperObject.h"
#include "Thread.h"

namespace cppthreads_starter_utils {

	/**
	 *	The starter method used by the pthread lib to call Runnber.run()
	 */
	extern "C" void * init(void *);

}

namespace cppthreads {

	class Runnable: public SuperObject {
		private:
			/**
			 * Runnable status
			 */
			bool running_;
		public:
			virtual void run() = 0;
			virtual ~Runnable(){
			}

			friend void * cppthreads_starter_utils::init(void *);
			bool isRunning(){ return running_; }

	};
}
#endif /* RUNNABLE_H_ */
