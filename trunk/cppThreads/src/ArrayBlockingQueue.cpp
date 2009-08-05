/*
 * LinkedBlockingQueue.cpp
 *
 *  Created on: May 5, 2009
 *      Author: ahmed soliman
 */

#include "ArrayBlockingQueue.h"
#include "OutOfSpaceException.h"

namespace cppthreads {
	ArrayBlockingQueue::ArrayBlockingQueue() :
		initialCapacity_(MAX_VALUE), limited_(false) {
		readSem_ = new Semaphore();
		writeSem_ = new Semaphore(MAX_VALUE);
		lock_ = new Mutex();
		backend_ = new std::vector<SuperObject *>();
	}
	ArrayBlockingQueue::ArrayBlockingQueue(uint32_t capacity) :
		initialCapacity_(capacity), limited_(true) {
		readSem_ = new Semaphore();
		writeSem_ = new Semaphore(initialCapacity_);
		lock_ = new Mutex();
		backend_ = new std::vector<SuperObject *>();
	}

	bool ArrayBlockingQueue::add(SuperObject *object) {
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
	bool ArrayBlockingQueue::offer(SuperObject *object) {
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
	bool ArrayBlockingQueue::offer(SuperObject *object, uint32_t timeout) {
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
	void ArrayBlockingQueue::put(SuperObject *object) {
		lock_->lock();

		writeSem_->wait();
		readSem_->signal();
		backend_->push_back(object);

		lock_->unlock();
	}

	bool ArrayBlockingQueue::remove(SuperObject *object) {
		lock_->lock();
		bool ret = false;
		std::vector<SuperObject *>::iterator myIterator;
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
	SuperObject *ArrayBlockingQueue::poll(uint32_t timeout) {
		SuperObject *ret = NULL;
		lock_->lock();
		if (readSem_->wait(timeout)) {
			ret = backend_->front();
			backend_->erase(backend_->begin());
			writeSem_->signal();
		}
		lock_->unlock();
		return ret;
	}

	SuperObject *ArrayBlockingQueue::take() {
		SuperObject *ret = NULL;
		lock_->lock();
		readSem_->wait();
		ret = backend_->front();
		backend_->erase(backend_->begin());
		writeSem_->signal();
		lock_->unlock();
		return ret;
	}

	SuperObject *ArrayBlockingQueue::peek() {
		SuperObject *ret = NULL;
		lock_->lock();
		if (size_()) {
			ret = backend_->front();
		}
		lock_->unlock();
		return ret;
	}

	bool ArrayBlockingQueue::contains(SuperObject *object) {
		lock_->lock();
		bool ret = false;
		std::vector<SuperObject *>::iterator myIterator;
		for (myIterator = backend_->begin(); myIterator != backend_->end(); myIterator++) {
			if (object == *myIterator) {
				ret = true;
				break;
			}
		}
		lock_->unlock();
		return ret;
	}

	uint32_t ArrayBlockingQueue::remainingCapacity() {
		lock_->lock();
		uint32_t ret = remainingCapacity_();
		lock_->unlock();
		return ret;
	}

	uint32_t ArrayBlockingQueue::getCapacity() {
		lock_->lock();
		uint32_t capacity = initialCapacity_;
		lock_->unlock();
		return capacity;
	}
	uint32_t ArrayBlockingQueue::remainingCapacity_() {
		uint32_t ret = MAX_VALUE;
		if (limited_) {
			ret = initialCapacity_ - readSem_->getValue();
		}
		return ret;
	}
	bool ArrayBlockingQueue::canAdd_() {
		bool ret = true;
		if (limited_ && this->remainingCapacity() == 0) {
			ret = false;
		}
		return ret;
	}

	uint32_t ArrayBlockingQueue::size() {
		lock_->lock();
		uint32_t ret = size_();
		lock_->unlock();
		return ret;
	}
	uint32_t ArrayBlockingQueue::size_() {
		uint32_t ret = readSem_->getValue();
		return ret;
	}

	ArrayBlockingQueue::~ArrayBlockingQueue() {
		delete readSem_;
		delete writeSem_;
		delete lock_;
		std::vector<SuperObject *>::iterator myIterator;
		for (myIterator = backend_->begin(); myIterator != backend_->end(); myIterator++) {
			delete *myIterator;
		}
		delete backend_;
	}
}
