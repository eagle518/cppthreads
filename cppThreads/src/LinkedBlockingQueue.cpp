/*
 * LinkedBlockingQueue.cpp
 *
 *  Created on: May 5, 2009
 *      Author: ahmed soliman
 */

#include "LinkedBlockingQueue.h"
#include "OutOfSpaceException.h"

namespace cppthreads {
	LinkedBlockingQueue::LinkedBlockingQueue() :
		initialCapacity_(MAX_VALUE), limited_(false) {
		readSem_ = new Semaphore();
		writeSem_ = new Semaphore(MAX_VALUE);
		lock_ = new Mutex();
		backend_ = new std::list<SuperObject *>();
	}
	LinkedBlockingQueue::LinkedBlockingQueue(uint32_t capacity) :
		initialCapacity_(capacity), limited_(true) {
		readSem_ = new Semaphore();
		writeSem_ = new Semaphore(initialCapacity_);
		lock_ = new Mutex();
		backend_ = new std::list<SuperObject *>();
	}

	bool LinkedBlockingQueue::add(SuperObject *object) {
		lock_->lock();
		if (remainingCapacity_() == 0) {
			lock_->unlock();
			throw OutOfSpaceException("No space remaining in the queue", 0);
		}
		writeSem_->wait();
		readSem_->signal();
		backend_->push_back(object);
		lock_->unlock();
		return true;
	}
	bool LinkedBlockingQueue::offer(SuperObject *object) {
		lock_->lock();
		bool ret = false;
		if (remainingCapacity_() > 0) {
			writeSem_->wait();
			backend_->push_back(object);
			readSem_->signal();
			ret = true;
		}
		lock_->unlock();
		return ret;
	}
	bool LinkedBlockingQueue::offer(SuperObject *object, uint32_t timeout) {
		lock_->lock();
		bool ret = false;

		bool res = writeSem_->wait(timeout);
		if (res) {
			backend_->push_back(object);
			readSem_->signal();
			ret = true;
		}
		lock_->unlock();
		return ret;

	}
	void LinkedBlockingQueue::put(SuperObject *object) {
		lock_->lock();

		writeSem_->wait();
		readSem_->signal();
		backend_->push_back(object);

		lock_->unlock();
	}

	bool LinkedBlockingQueue::remove(SuperObject *object) {
		lock_->lock();
		bool ret = false;
		std::list<SuperObject *>::iterator myIterator;
		for (myIterator = backend_->begin(); myIterator != backend_->end(); myIterator++) {
			if (object == *myIterator) {
				backend_->erase(myIterator);
				readSem_->wait();
				ret = true;
				break;
			}
		}
		lock_->unlock();
		return ret;
	}
	SuperObject *LinkedBlockingQueue::poll(uint32_t timeout) {
		SuperObject *ret = NULL;
		lock_->lock();
		if (readSem_->wait(timeout)) {
			ret = backend_->front();
			backend_->pop_front();
			writeSem_->signal();
		}
		lock_->unlock();
		return ret;
	}

	SuperObject *LinkedBlockingQueue::take() {
		SuperObject *ret = NULL;
		lock_->lock();
		readSem_->wait();
		ret = backend_->front();
		backend_->pop_front();
		writeSem_->signal();
		lock_->unlock();
		return ret;
	}

	SuperObject *LinkedBlockingQueue::peek() {
		SuperObject *ret = NULL;
		lock_->lock();
		if (size_()) {
			ret = backend_->front();
		}
		lock_->unlock();
		return ret;
	}

	bool LinkedBlockingQueue::contains(SuperObject *object) {
		lock_->lock();
		bool ret = false;
		std::list<SuperObject *>::iterator myIterator;
		for (myIterator = backend_->begin(); myIterator != backend_->end(); myIterator++) {
			if (object == *myIterator) {
				ret = true;
				break;
			}
		}
		lock_->unlock();
		return ret;
	}

	uint32_t LinkedBlockingQueue::remainingCapacity() {
		lock_->lock();
		uint32_t ret = remainingCapacity_();
		lock_->unlock();
		return ret;
	}

	uint32_t LinkedBlockingQueue::getCapacity() {
		lock_->lock();
		uint32_t capacity = initialCapacity_;
		lock_->unlock();
		return capacity;
	}
	uint32_t LinkedBlockingQueue::remainingCapacity_() {
		uint32_t ret = MAX_VALUE;
		if (limited_) {
			ret = initialCapacity_ - readSem_->getValue();
		}
		return ret;
	}
	bool LinkedBlockingQueue::canAdd_() {
		bool ret = true;
		if (limited_ && this->remainingCapacity() == 0) {
			ret = false;
		}
		return ret;
	}

	uint32_t LinkedBlockingQueue::size() {
		lock_->lock();
		uint32_t ret = size_();
		lock_->unlock();
		return ret;
	}
	uint32_t LinkedBlockingQueue::size_() {
		uint32_t ret = readSem_->getValue();
		return ret;
	}

	LinkedBlockingQueue::~LinkedBlockingQueue() {
		delete readSem_;
		delete writeSem_;
		delete lock_;
		std::list<SuperObject *>::iterator myIterator;
		for (myIterator = backend_->begin(); myIterator != backend_->end(); myIterator++) {
			delete *myIterator;
		}
		delete backend_;
	}
}
