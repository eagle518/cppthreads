/*
 * Thread.h
 *
 *  Created on: May 5, 2009
 *      Author: Abd4llA
 */

#ifndef RUNNABLE_H_
#define RUNNABLE_H_
#include "SuperObject.h"

class Runnable: public SuperObject {
	private:

	public:
		virtual void run() = 0;
};

#endif /* RUNNABLE_H_ */
