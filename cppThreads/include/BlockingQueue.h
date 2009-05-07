/*
 * BlockingQueue.h
 *
 *  Created on: May 5, 2009
 *      Author: ahmed soliman
 */

#ifndef BLOCKINGQUEUE_H_
#define BLOCKINGQUEUE_H_
#include "SuperObject.h"

class BlockingQueue : public SuperObject{
public:
	BlockingQueue();
	virtual bool add(SuperObject *object)=0;
	virtual bool offer(SuperObject *object)=0;
	virtual bool offer(SuperObject *object, int32_t timeout)=0;
	virtual void put(SuperObject *object)=0;

	virtual bool remove(SuperObject *object)=0;
	virtual SuperObject *poll(int32_t timeout)=0;
	virtual SuperObject *poll()=0;
	virtual SuperObject *take()=0;
	virtual SuperObject *element()=0;
	virtual SuperObject *peek()=0;

	virtual bool contains(SuperObject *object)=0;
	virtual int32_t remainingCapacity()=0;
	virtual int32_t getCapacity()=0;


	virtual ~BlockingQueue() {};
};

#endif /* BLOCKINGQUEUE_H_ */
