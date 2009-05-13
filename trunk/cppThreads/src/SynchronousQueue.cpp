/*
 * SynchronousQueue.cpp
 *
 *  Created on: May 5, 2009
 *      Author: ahmed soliman
 */

#include "SynchronousQueue.h"
namespace cppthreads {
	SynchronousQueue::SynchronousQueue() {
		lock_ = new Mutex();
		producerOffers_ = new Semaphore();
		consumerRequests_ = new Semaphore();
		theSoleObject_ = NULL;
	}

	bool SynchronousQueue::add(SuperObject *object) {
		return offer(object);
	}

	bool SynchronousQueue::offer(SuperObject *object) {
		return trySetObject_(object);
	}
	bool SynchronousQueue::offer(SuperObject *object, uint32_t timeout) {
		return timedGetObject_(timeout);
	}

	void SynchronousQueue::put(SuperObject *object) {
		setObject_(object);
	}

	bool SynchronousQueue::remove(SuperObject *object) {
		return false;
	}
	SuperObject *SynchronousQueue::poll(uint32_t timeout) {
		return timedGetObject_(timeout);
	}

	SuperObject *SynchronousQueue::take() {
		return getObject_();
	}

	SuperObject *SynchronousQueue::peek() {
		return NULL;
	}

	bool SynchronousQueue::contains(SuperObject *object) {
		return false;
	}

	uint32_t SynchronousQueue::remainingCapacity() {
		return 0;
	}

	uint32_t SynchronousQueue::getCapacity() {
		return 0;
	}

	uint32_t SynchronousQueue::size() {
		return 0;
	}

	SuperObject *SynchronousQueue::tryGetObject_() {
		// Not the most efficient implementation IMHO
		// TODO: add support for piping for parallel handing.
		// TODO: consider using conditional variables here
		SuperObject *ret = NULL;
		lock_->lock();
		consumerRequests_->signal();
		if (!producerOffers_->tryWait()) {
			consumerRequests_->wait();
			lock_->unlock();
			return NULL;
		}
		ret = theSoleObject_;
		lock_->unlock();
		return ret;
	}
	SuperObject *SynchronousQueue::timedGetObject_(uint32_t timeout) {
		// Not the most efficient implementation IMHO
		// TODO: add support for piping for parallel handing.
		// TODO: consider using conditional variables here
		SuperObject *ret = NULL;
		lock_->lock();
		consumerRequests_->signal();
		if (!producerOffers_->wait(timeout)) {
			consumerRequests_->wait();
			lock_->unlock();
			return NULL;
		}
		ret = theSoleObject_;
		lock_->unlock();
		return ret;
	}

	SuperObject *SynchronousQueue::getObject_() {
		// Not the most efficient implementation IMHO
		// TODO: add support for piping for parallel handing.
		// TODO: consider using conditional variables here
		SuperObject *ret = NULL;
		lock_->lock();
		consumerRequests_->signal();
		producerOffers_->wait();
		ret = theSoleObject_;
		theSoleObject_ = NULL;
		lock_->unlock();
		return ret;
	}
	void SynchronousQueue::setObject_(SuperObject *object) {
		lock_->lock();
		consumerRequests_->wait();
		theSoleObject_ = object;
		producerOffers_->signal();
		lock_->unlock();
	}

	bool SynchronousQueue::trySetObject_(SuperObject *object) {
		lock_->lock();
		if (!consumerRequests_->tryWait()) {
			lock_->unlock();
			return false;
		}
		theSoleObject_ = object;
		producerOffers_->signal();
		lock_->unlock();
		return true;
	}

	bool SynchronousQueue::timedSetObject_(SuperObject *object, uint32_t timeout) {
		lock_->lock();
		if (!consumerRequests_->wait(timeout)) {
			lock_->unlock();
			return false;
		}
		theSoleObject_ = object;
		producerOffers_->signal();
		lock_->unlock();
		return true;
	}
	SynchronousQueue::~SynchronousQueue() {
		delete lock_;
		delete producerOffers_;
		delete consumerRequests_;
	}
}
