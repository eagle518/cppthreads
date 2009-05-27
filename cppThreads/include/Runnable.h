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

namespace cppthreads {

	class Runnable: public SuperObject {
		public:
			virtual void run() = 0;
			Runnable(){}
			virtual ~Runnable(){}

	};
}
#endif /* RUNNABLE_H_ */
