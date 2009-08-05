/*
 * LinkedBlockingQueue.h
 *
 *  Created on: May 5, 2009
 *      Author: ahmed soliman
 */

#ifndef LINKEDBLOCKINGQUEUE_H_
#define LINKEDBLOCKINGQUEUE_H_

#include "BlockingQueue.h"
#include "Semaphore.h"
#include "Mutex.h"
#include <vector>

namespace cppthreads {
	class ArrayBlockingQueue: public BlockingQueue {
		public:
			ArrayBlockingQueue();
			ArrayBlockingQueue(uint32_t capacity);

			/**
			 * Inserts the specified element into this queue if it is possible to do so immediately without violating capacity restrictions,
			 * returning true upon success and throwing an OutOfSpaceException if no space is currently available.
			 */
			virtual bool add(SuperObject *object);
			/**
			 * Inserts the specified element into this queue if it is possible to do so immediately without violating capacity restrictions,
			 * returning true upon success and false if no space is currently available.
			 */
			virtual bool offer(SuperObject *object);
			/**
			 * Inserts the specified element into this queue, waiting up to the specified wait time if necessary for space to become available.
			 * returns true if the element was put successfully before timeout, false if the specified time elapses before space is available.
			 * timeout is in milli-seconds
			 */
			virtual bool offer(SuperObject *object, uint32_t timeout);
			/**
			 * Inserts the specified element into this queue, waiting if necessary for space to become available
			 */
			virtual void put(SuperObject *object);
			/**
			 * Removes a single instance of the specified element from this queue, if it is present. the element is removed if the object passed
			 * shared the same memory address as the object in the queue.
			 * returns true if the element was removed, false if it's not there.
			 */
			virtual bool remove(SuperObject *object);
			/**
			 * Retrieves and removes the head of this queue, waiting up to the specified wait time if necessary for an element to become available.
			 * returns NULL if the time elapsed before an element was available.
			 */
			virtual SuperObject *poll(uint32_t timeout);
			/**
			 * Retrieves and removes the head of this queue, waiting if necessary until an element becomes available.
			 */
			virtual SuperObject *take();
			/**
			 * Retrieves, but does not remove, the head of this queue, or returns null if this queue is empty.
			 */
			virtual SuperObject *peek();
			/**
			 * Returns true if this queue contains the specified element. (comparison is memory address based)
			 */
			virtual bool contains(SuperObject *object);
			/**
			 * Returns the number of additional elements that this queue can ideally (in the absence of memory or
			 * resource constraints) accept without blocking, or BlockingQueue::MAX_VALUE if there is no intrinsic limit.
			 */
			virtual uint32_t remainingCapacity();
			/**
			 * Returns the original capacity of the queue.
			 */
			virtual uint32_t getCapacity();
			/**
			 * Returns the count of the elements currently in the queue
			 */
			virtual uint32_t size();

			virtual ~ArrayBlockingQueue();
		private:
			uint32_t remainingCapacity_();
			bool canAdd_();
			uint32_t size_();
			std::vector<SuperObject *> *backend_;
			uint32_t initialCapacity_;

			bool limited_;
			/**
			 * we are using pointers here because there are certainn situations where you
			 * don't want to instantiate both semaphores.
			 */
			// will block on read when the queue is empty, its value is the size of the queue
			Semaphore *readSem_;
			// will block on write when you don't have any free space, its value is the remainingCapacity
			Semaphore *writeSem_;

			Mutex *lock_;

	};
}
#endif /* LINKEDBLOCKINGQUEUE_H_ */
