/*
 * ThreadTest.cpp
 *
 *  Created on: May 15, 2009
 *      Author: Abd4llA
 */
#include <gtest/gtest.h>
#include <sys/types.h>
#include <vector>
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
			elements_->addElement(1);
		}
	private:
		SynchornizedList  *elements_;
};
class ThreadTest : public ::testing::Test {
	protected:
		SynchornizedList *myList_;
		Thread *thread1 ;
		Thread *thread2;
		Thread *thread3;

		virtual void SetUp(){
			myList_ = new SynchornizedList();
			thread1 = new Thread(new RunnableObject(myList_));
			thread2 = new Thread(new RunnableObject(myList_));
			thread3 = new Thread(new RunnableObject(myList_));
		}
		virtual void TearDown(){
			delete thread1;
			delete thread2;
			delete thread3;
			delete myList_;
		}
};

TEST_F(ThreadTest, ThreadsRun){
	ASSERT_FALSE(thread1->isRunning());
	thread1->start();
	ASSERT_FALSE(thread2->isRunning());
	thread2->start();
	ASSERT_FALSE(thread3->isRunning());
	thread3->start();
	thread1->join();
	thread2->join();
	thread3->join();
	ASSERT_EQ(3, myList_->getSize());
}
TEST_F(ThreadTest, ThreadsJoinable){
	thread1->start();
	thread1->join();
	ASSERT_FALSE(thread1->isRunning());
	ASSERT_EQ(1,myList_->getSize());
}
TEST_F(ThreadTest, ThreadsRestartingFails){
	thread1->start();
	thread1->join();
	ASSERT_THROW(thread1->start(), ThreadAlreadyStartedException);
}
