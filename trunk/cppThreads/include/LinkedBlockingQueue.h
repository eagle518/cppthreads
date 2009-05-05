/*
 * LinkedBlockingQueue.h
 *
 *  Created on: May 5, 2009
 *      Author: ahmed soliman
 */

#ifndef LINKEDBLOCKINGQUEUE_H_
#define LINKEDBLOCKINGQUEUE_H_

#include "BlockingQueue.h"

class LinkedBlockingQueue: public BlockingQueue {
public:
	LinkedBlockingQueue();
	virtual ~LinkedBlockingQueue();
};

#endif /* LINKEDBLOCKINGQUEUE_H_ */
