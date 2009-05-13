/*
 * BlockingQueue.h
 *
 *  Created on: May 5, 2009
 *      Author: ahmed soliman
 */

#ifndef BLOCKINGQUEUE_H_
#define BLOCKINGQUEUE_H_
#include "SuperObject.h"
#include <iostream>
#include <limits.h>
#include "Semaphore.h"
namespace cppthreads {
	/**
	 * Blocking queues are queues that block its reader or writer if there are no elements or there is no remaining capacity, respectively.
	 * NOTE: All blocking queue that has storage will take ownership of the inner objects, this means that if you destroy the queue, it'll
	 * delete all the pointers of the objects inside the queue at then.
	 */
	class BlockingQueue: public SuperObject {
		public:
			static const uint32_t MAX_VALUE = Semaphore::MAX_VALUE;
			/**
			 * Inserts the specified element into this queue if it is possible to do so immediately without violating capacity restrictions,
			 * returning true upon success and throwing an OutOfSpaceException if no space is currently available.
			 */
			virtual bool add(SuperObject *object)=0;
			/**
			 * Inserts the specified element into this queue if it is possible to do so immediately without violating capacity restrictions,
			 * returning true upon success and false if no space is currently available.
			 */
			virtual bool offer(SuperObject *object)=0;
			/**
			 * Inserts the specified element into this queue, waiting up to the specified wait time if necessary for space to become available.
			 * returns true if the element was put successfully before timeout, false if the specified time elapses before space is available.
			 * timeout is in milli-seconds
			 */
			virtual bool offer(SuperObject *object, uint32_t timeout)=0;
			/**
			 * Inserts the specified element into this queue, waiting if necessary for space to become available
			 */
			virtual void put(SuperObject *object)=0;
			/**
			 * Removes a single instance of the specified element from this queue, if it is present. the element is removed if the object passed
			 * shared the same memory address as the object in the queue.
			 * returns true if the element was removed, false if it's not there.
			 */
			virtual bool remove(SuperObject *object)=0;
			/**
			 * Retrieves and removes the head of this queue, waiting up to the specified wait time if necessary for an element to become available.
			 * returns NULL if the time elapsed before an element was available.
			 */
			virtual SuperObject *poll(uint32_t timeout)=0;
			/**
			 * Retrieves and removes the head of this queue, waiting if necessary until an element becomes available.
			 */
			virtual SuperObject *take()=0;
			/**
			 * Retrieves, but does not remove, the head of this queue, or returns null if this queue is empty.
			 */
			virtual SuperObject *peek()=0;
			/**
			 * Returns true if this queue contains the specified element. (comparison is memory address based)
			 */
			virtual bool contains(SuperObject *object)=0;
			/**
			 * Returns the number of additional elements that this queue can ideally (in the absence of memory or
			 * resource constraints) accept without blocking, or BlockingQueue::MAX_VALUE if there is no intrinsic limit.
			 */
			virtual uint32_t remainingCapacity()=0;
			/**
			 * Returns the original capacity of the queue.
			 */
			virtual uint32_t getCapacity()=0;
			/**
			 * Returns the count of the elements currently in the queue
			 */
			virtual uint32_t size()=0;

			virtual ~BlockingQueue() {
			}
	};
}
#endif /* BLOCKINGQUEUE_H_ */
