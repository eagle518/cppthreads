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
#include <string>
using namespace std;

/**
 *	the pthread method
 */
void * init(void *);

namespace cppthreads {
	class Thread: public Runnable, public SuperObject {
		private:
			/**
			 * Thread priority
			 */
			int priority;
			/**
			 * Unique thread ID
			 */
			int id;
			/**
			 *
			 */
			void * returnResult;
			string name;
			/**
			 * Our runnable object, it should be passed in the constructor
			 */
			Runnable * target;
			pthread_t * pthread;
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
		public:
			/**
			 * Creates a new Thread object that'll call target's run method in a new execution thread
			 */
			Thread(Runnable & target);
			/**
			 * Creates a new Thread object with name that'll call target's run method in a new execution thread
			 */
			Thread(Runnable & target, string name);

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
			void sleep(int millis);
			/**
			 * Wait until this thread finish execution.
			 * Thread calling this join() will block until this Thread finishes execution
			 */
			void join();
			/**
			 * Wait until thread finish execution up to timeout which is expressed in millis
			 */
			void join(int timeout);

			int getPriority() const;

			void setPriority(int priority);

			int getId() const;

			string getName() const;

			void setName(string name);


	};
}
#endif /* THREAD_H_ */
