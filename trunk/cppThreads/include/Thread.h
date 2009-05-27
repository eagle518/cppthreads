/*
 * Thread.h
 *
 *  Created on: May 5, 2009
 *      Author: Abd4llA
 */

#ifndef THREAD_H_
#define THREAD_H_
#include "Runnable.h"
#include "SuperObject.h"
#include <iostream>
#include <pthread.h>
#include "Mutex.h"
#include <string>
#include <sys/types.h>
#include <time.h>
using namespace std;

namespace cppthreads_starter_utils {

	/**
	 *	The starter method used by the pthread lib to call Runnber.run()
	 */
	extern "C" void * init(void *);

}

namespace cppthreads {
	class Thread: public Runnable {
		public:
			/**
			 * Creates a new Thread object that'll call target's run method in a new execution thread
			 */
			Thread(Runnable *target);
			/**
			 * Creates a new Thread object with name that'll call target's run method in a new execution thread
			 */
			Thread(Runnable *target, string name);

			~Thread();

			/**
			 * Starts execution of
			 */
			void start();
			/**
			 * The start method of the new thread.
			 * Override this method and put the code which you want to run in a new thread inside.
			 */
			virtual void run();
			/**
			 * Puts thread to sleep for "millis" seconds
			 */
			void sleep(int32_t millis);
			/**
			 * Wait until this thread finish execution.
			 * Thread calling this join() will block until this Thread finishes execution
			 */
			void join();
			/**
			 * Wait until thread finish execution up to timeout which is expressed in millis
			 */
			void join(int timeout);
			/**
			 * Check if thread is running
			 */
			bool isRunning();
			/**
			 * Yield current execution and wait in the run queue
			 */
			void yield();

			int32_t getPriority() const;

			void setPriority(int32_t priority);

			int32_t getId() const;

			string getName() const;

			void setName(string name);

		private:
			/**
			 * Thread priority
			 */
			int32_t priority_;
			/**
			 * Unique thread ID
			 */
			int32_t id_;
			/**
			 * The return value of the thread we join
			 */
			void * returnResult_;
			/**
			 * Thread name
			 */
			string name_;

			/**
			 * Our runnable object, it should be passed in the constructor
			 */
			Runnable *target_;
			/**
			 * To provide thread safety for all operations in Thread class.
			 */
			Mutex lock_;

			/**
			 * To be used in timed join to unblock when a thread finishes
			 */
			pthread_cond_t threadTerminatedCond_;
			/**
			 * To be used in timed join as well
			 */

			/**
			 * POSIX Thread handle
			 */
			pthread_t threadHandle_;
			/**
			 * Thread started once;
			 */
			bool started_;
			/**
			 * initiaizer method
			 */
			void init_();
			/**
			 * args array to be sent to init
			 * args[0] : Runnable target
			 * args[1] : "this" pointer
			 */
			void * args_[2];
			/**
			 * Runnable status
			 */
			bool running_;

			friend void * cppthreads_starter_utils::init(void *);
		protected:
			/**
			 * Default constructor.
			 * Can only be used if you extend Thread to override the run method.
			 */
			Thread();
			/**
			 * Creates a new Thread and sets its name.
			 */
			Thread(string name);
	};
}
#endif /* THREAD_H_ */
