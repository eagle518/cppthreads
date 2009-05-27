/*
 * ThreadTest.cpp
 *
 *  Created on: May 15, 2009
 *      Author: Abd4llA
 */
#include <gtest/gtest.h>
#include <sys/types.h>
#include <vector>
#include <time.h>
#include "Thread.h"
#include "Runnable.h"
#include "Mutex.h"
#include "ThreadAlreadyStartedException.h"

using namespace cppthreads;
using namespace std;

class SynchornizedList : public SuperObject {
	public:
		SynchornizedList() : container_(new vector<int32_t>()) {

		}
		void addElement(int32_t value) {
			lock_.lock();
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
			for (int i =0; i<100;i++) {
//				cout << "Adding Element " << i + 1 << endl;
				elements_->addElement(i);
//				usleep(100);
			}

		}
		~RunnableObject(){
			cout << "RunnableObject deleting: " << this << endl;
		}
	private:
		SynchornizedList  *elements_;
};

TEST(ThreadTest, ThreadsRun){
	SynchornizedList *myList_;
	Runnable * runnable;
	Thread *thread1 ;
	Thread *thread2;
	Thread *thread3;

	myList_ = new SynchornizedList();
	thread1 = new Thread(new RunnableObject(myList_));
	thread2 = new Thread(new RunnableObject(myList_));
	thread3 = new Thread(new RunnableObject(myList_));

	ASSERT_FALSE(thread1->isRunning());
	thread1->start();
	ASSERT_FALSE(thread2->isRunning());
	thread2->start();
	ASSERT_FALSE(thread3->isRunning());
	thread3->start();
	cout  << "Joining Threads..." << endl;
	thread1->join();
	thread2->join();
	thread3->join();
	ASSERT_EQ(300, myList_->getSize());

	delete thread1;
	delete thread2;
	delete thread3;
	delete myList_;

}
TEST(ThreadTest, ThreadsJoinable){
	SynchornizedList *myList_;
	Runnable * runnable;
	Thread *thread1 ;

	myList_ = new SynchornizedList();
	thread1 = new Thread(new RunnableObject(myList_));

	cout << "Starting Thread" << endl;
	thread1->start();
	cout << "Joining thread1" << endl;
	thread1->join(3);
	cout << "Joining thread2" << endl;
	ASSERT_FALSE(thread1->isRunning());
	ASSERT_EQ(100, myList_->getSize());

	delete thread1;
	delete myList_;

}

TEST(ThreadTest, ThreadsJoinable2){
	SynchornizedList *myList_;
	Runnable * runnable;
	Thread *thread1 ;

	myList_ = new SynchornizedList();
	thread1 = new Thread(new RunnableObject(myList_));

	cout << "Starting Thread" << endl;
	thread1->start();
	cout << "Joining thread1" << endl;
	// will make sure that you have the thread started already..
	usleep(10);
	thread1->join(3);
	cout << "Joining thread2" << endl;
	ASSERT_FALSE(thread1->isRunning());
	ASSERT_EQ(100, myList_->getSize());

	delete thread1;
	delete myList_;

}

TEST(ThreadTest, ThreadsJoinable3){
	SynchornizedList *myList_;
	Runnable * runnable;
	Thread *thread1 ;

	myList_ = new SynchornizedList();
	thread1 = new Thread(new RunnableObject(myList_));

	cout << "Starting Thread" << endl;
	cout << "Joining thread1" << endl;
	thread1->join(3);
	thread1->start();
	cout << "Joining thread2" << endl;
	thread1->join();
	ASSERT_EQ(100, myList_->getSize());

	delete thread1;
	delete myList_;

}

TEST(ThreadTest, ThreadsJoinable1){
	SynchornizedList *myList_;
	Runnable * runnable;
	Thread *thread1 ;

	myList_ = new SynchornizedList();
	thread1 = new Thread(new RunnableObject(myList_));

	cout << "Starting Thread" << endl;
	thread1->start();
	usleep(2000);
	cout << "Joining thread1" << endl;
	thread1->join(3);
	cout << "Joining thread2" << endl;
	ASSERT_FALSE(thread1->isRunning());
	ASSERT_EQ(100, myList_->getSize());

	delete thread1;
	delete myList_;

}
TEST(ThreadTest, ThreadsRestartingFails){
	SynchornizedList *myList_;
	Runnable * runnable;
	Thread *thread1 ;
	Thread *thread2;
	Thread *thread3;

	myList_ = new SynchornizedList();
	thread1 = new Thread(new RunnableObject(myList_));
	thread2 = new Thread(new RunnableObject(myList_));
	thread3 = new Thread(new RunnableObject(myList_));

	thread1->start();
	thread1->join();
	ASSERT_THROW(thread1->start(), ThreadAlreadyStartedException);

	delete thread1;
	delete thread2;
	delete thread3;
	delete myList_;

}
