/*
 * SynchronousQueue.h
 *
 *  Created on: May 5, 2009
 *      Author: ahmed soliman
 */

#ifndef SYNCHRONOUSQUEUE_H_
#define SYNCHRONOUSQUEUE_H_

#include "BlockingQueue.h"

class SynchronousQueue: public BlockingQueue {
public:
	SynchronousQueue();
	virtual ~SynchronousQueue();
};

#endif /* SYNCHRONOUSQUEUE_H_ */
