#ifndef SUPEROBJECT_H_
#define SUPEROBJECT_H_

#include <stdint.h>
#include <stdio.h>
#include <pthread.h>
#include <sstream>
/**
 * Super object is similar to "object" in java that is the parent of any class that you want to put
 * in any of cppThreads containers or to be used in threading, because of the multiple inheritance in C++
 * you can easily integrate that into any of your projects easily.
 */
class SuperObject {
	public:
		virtual ~SuperObject();
		virtual const char *toString() const{
			return "SuperObject <Standard>";
			};
		void wait();
		bool wait(uint32_t timeOut);
		void notify();
		void notifyAll();

	protected:
		SuperObject();
		pthread_cond_t condHandle_;
		pthread_mutex_t globalMutexHandle_;
};

#endif /* SUPEROBJECT_H_ */
