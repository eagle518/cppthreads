/*
 * LinkedBlockingQueue.cpp
 *
 *  Created on: May 5, 2009
 *      Author: ahmed soliman
 */

#include "LinkedBlockingQueue.h"

namespace cppthreads {
	LinkedBlockingQueue::LinkedBlockingQueue() : initialCapacity_(MAX_VALUE){

	}
	LinkedBlockingQueue::LinkedBlockingQueue(uint32_t capacity) : initialCapacity_(capacity){

	}

	bool LinkedBlockingQueue::add(SuperObject *object) {

	}
	bool LinkedBlockingQueue::offer(SuperObject *object) {
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

	}
	uint32_t LinkedBlockingQueue::getCapacity() {

	}


	LinkedBlockingQueue::~LinkedBlockingQueue() {
		// TODO Auto-generated destructor stub
	}
}
