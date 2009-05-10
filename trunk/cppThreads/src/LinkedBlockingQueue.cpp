/*
 * LinkedBlockingQueue.cpp
 *
 *  Created on: May 5, 2009
 *      Author: ahmed soliman
 */

#include "LinkedBlockingQueue.h"

namespace cppthreads {
	LinkedBlockingQueue::LinkedBlockingQueue() : initialCapacity_(MAX_VALUE), limited_(false){
		readSem_ = new Semaphore();
		writeSem_ = new Semaphore(initialCapacity_);
	}
	LinkedBlockingQueue::LinkedBlockingQueue(uint32_t capacity) : initialCapacity_(capacity), limited_(true){
		readSem_ = new Semaphore();
		writeSem_ = new Semaphore(initialCapacity_);
	}

	bool LinkedBlockingQueue::add(SuperObject *object) {
		writeSem_->post();

	}
	bool LinkedBlockingQueue::offer(SuperObject *object) {
		writeSem_->post();
	}
	bool LinkedBlockingQueue::offer(SuperObject *object, uint32_t timeout) {

	}
	void LinkedBlockingQueue::put(SuperObject *object) {

	}
	bool remove(SuperObject *object) {

	}
	SuperObject *LinkedBlockingQueue::poll(uint32_t timeout) {

	}
	SuperObject *LinkedBlockingQueue::take() {

	}
	SuperObject *LinkedBlockingQueue::element() {

	}
	SuperObject *LinkedBlockingQueue::peek() {

	}

	bool LinkedBlockingQueue::contains(SuperObject *object) {

	}

	uint32_t LinkedBlockingQueue::remainingCapacity() {
		uint32_t ret = MAX_VALUE;
		if (limited_) {
			ret = initialCapacity_ - readSem_->getValue();
		}
		return ret;
	}

	uint32_t LinkedBlockingQueue::getCapacity() {
		return initialCapacity_;
	}

	bool LinkedBlockingQueue::canAdd_() {
		bool ret = true;
		if (limited_ && this->remainingCapacity() == 0) {
				ret = false;
		}
		return ret;
	}

	LinkedBlockingQueue::~LinkedBlockingQueue() {
		// TODO Auto-generated destructor stub
	}
}
