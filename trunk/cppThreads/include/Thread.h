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
using namespace std;

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
			 * POSIX Thread handle
			 */
			pthread_t threadHandle_;
			/**
			 * Thread started once;
			 */
			bool started_;
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
