/*
 * Thread.cpp
 *
 *  Created on: May 7, 2009
 *      Author: Abd4llA
 */

#include "Thread.h"
#include <pthread.h>

void * init(void * runnable) {
	cppthreads::Runnable *thread = static_cast<cppthreads::Runnable *> (runnable);
	thread->run();
}
namespace cppthreads {
	Thread::Thread(){
		target = this;
		pthread = new pthread_t;
	}
	Thread::Thread(string name) {
		this->name = name;
		target = this;
		pthread = new pthread_t;
	}

	Thread::Thread(Runnable & target) {
		this->target = &target;
		pthread = new pthread_t;
	}

	Thread::Thread(Runnable & target, string name) {
		this->name = name;
		this->target = &target;
		pthread = new pthread_t;
	}

	void Thread::start() {
		pthread_create(pthread, NULL, init, (void *) target);
	}

	/**
	 * The start method of the new thread.
	 * Override this method and put the code which you want to run in a new thread inside.
	 */
	void Thread::run(){

	}
	/**
	 * Puts thread to sleep for "millis" seconds
	 */
	void Thread::sleep(int millis){

	}
	/**
	 * Wait until this thread finish execution.
	 * Thread calling this join() will block until this Thread finishes execution
	 */
	void Thread::join(){
		pthread_join(*pthread, &returnResult);
	}
	/**
	 * Wait until thread finish execution up to timeout which is expressed in millis
	 */
	void Thread::join(int timeout){
	}

	int Thread::getPriority() const{
		return this->priority;
	}

	void Thread::setPriority(int priority){
		this->priority = priority;
	}

	int Thread::getId() const{
		return this->id;
	}

	string Thread::getName() const{
		return this->name;
	}

	void Thread::setName(string name){
		this->name = name;
	}

	Thread::~Thread() {
		// TODO Auto-generated destructor stub
		delete pthread;
	}

}
