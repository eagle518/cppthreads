/*
 * Test.cpp
 *
 *  Created on: May 25, 2009
 *      Author: Abd4llA
 */

#include <gtest/gtest.h>
#include <vector>
#include <time.h>
#include "Thread.h"
#include "Runnable.h"
#include "Mutex.h"
#include "AlreadyStartedException.h"

using namespace cppthreads;
using namespace std;
class SynchornizedList : public SuperObject {
	public:
		SynchornizedList() : container_(new vector<int32_t>()) {

		}
		void addElement(int32_t value) {
			lock_.lock();
			sleep(1);
			container_->push_back(value);
			lock_.unlock();
		}

		int32_t getSize() {
			lock_.lock();
			int32_t ret = container_->size();
			lock_.unlock();
			return ret;
		}
		~SynchornizedList() {
			delete container_;
		}
	protected:
		Mutex lock_;
		vector<int32_t> *container_;
};
class RunnableObject : public Runnable {
	public:
		RunnableObject(SynchornizedList *myList) : elements_(myList) {

		}
		void run(){
			//for (int i =0; i<1000;i++)
				elements_->addElement(1);

		}
		~RunnableObject(){
			delete elements_;
		}
	private:
		SynchornizedList  *elements_;
};
int main(){
	Thread * threads [100] ;
	for (int i = 0; i<100;i++){

		SynchornizedList * sl = new SynchornizedList();
		Thread * t1 = new Thread(new RunnableObject(sl));
		t1->start();
		cout << "Thread Started" << endl;
		cout << "Joined" << endl;
//		t1->join(100);
		threads[i] = t1;
	}
	threads[99]->join(100);
	for (int i=0;i<100;i++)
		delete threads[i];
}
