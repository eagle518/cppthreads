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
#include "ThreadAlreadyStartedException.h"

using namespace cppthreads;
using namespace std;
class RunnableObject : public Runnable {
	private:
		vector<int32_t>  * elements_;
		int32_t position_;
	public:
		RunnableObject(vector<int32_t> *elements,int32_t pos) : elements_(elements), position_(pos){

		}
		void run(){
			elements_->push_back(1);
		}
};
class ThreadTest : public ::testing::Test {
	protected:
		vector<int32_t> *container_;
		Thread *thread1 ;
		Thread *thread2;
		Thread *thread3;

		virtual void SetUp(){
			container_ = new vector<int32_t>();
			thread1 = new Thread(new RunnableObject(container_,0));
			thread2 = new Thread(new RunnableObject(container_,1));
			thread3 = new Thread(new RunnableObject(container_,2));
		}
		virtual void TearDown(){
			delete thread1;
			delete thread2;
			delete thread3;
			delete container_;
		}
};

TEST_F(ThreadTest, ThreadsRun){
	ASSERT_FALSE(thread1->isRunning());
	thread1->start();
	ASSERT_FALSE(thread2->isRunning());
	thread2->start();
	ASSERT_FALSE(thread3->isRunning());
	thread3->start();
	while ( thread1->isRunning() || thread2->isRunning() || thread3->isRunning())
		;
	ASSERT_EQ(3,container_->size());
}
TEST_F(ThreadTest, ThreadsJoinable){
	thread1->start();
	thread1->join();
	ASSERT_FALSE(thread1->isRunning());
	ASSERT_EQ(1,container_->size());
}
TEST_F(ThreadTest, ThreadsRestartingFails){
	thread1->start();
	while (thread1->isRunning())
		;
	ASSERT_THROW(thread1->start(),ThreadAlreadyStartedException);
}
