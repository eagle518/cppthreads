/*
 * ArrayBlockingQueue.h
 *
 *  Created on: May 5, 2009
 *      Author: ahmed soliman
 */

#ifndef ARRAYBLOCKINGQUEUE_H_
#define ARRAYBLOCKINGQUEUE_H_

#include "BlockingQueue.h"

class ArrayBlockingQueue: public BlockingQueue {
public:
	ArrayBlockingQueue();
	virtual ~ArrayBlockingQueue();
};

#endif /* ARRAYBLOCKINGQUEUE_H_ */
