#ifndef SUPEROBJECT_H_
#define SUPEROBJECT_H_

#include <sys/types.h>
/**
 * Super object is similar to "object" in java that is the parent of any class that you want to put
 * in any of cppThreads containers or to be used in threading, because of the multiple inheritance in C++
 * you can easily integrate that into any of your projects easily.
 */
class SuperObject {
	public:
		virtual ~SuperObject() {};

	protected:
		SuperObject() {};
};

#endif /* SUPEROBJECT_H_ */
