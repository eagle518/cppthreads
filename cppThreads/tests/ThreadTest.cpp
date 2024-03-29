/*
 * ThreadTest.cpp
 *
 *  Created on: May 15, 2009
 *      Author: Abd4llA
 */

#include <gtest/gtest.h>
#include <vector>
#include <time.h>
#include "Thread.h"
#include "Runnable.h"
#include "Mutex.h"
#include "AlreadyStartedException.h"
#include "TimeOutException.h"

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
			cout << " SynchronizedList " << this << " deleting container " << container_ << endl;
			delete container_;
			cout << "SynchronizedList deleted" << endl ;
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
			for (int i =0; i < 100; i++) {
				elements_->addElement(i);
			}

		}
	private:
		SynchornizedList  *elements_;
};

class LongRunObj : public Runnable {
	//A runnable that takes too long to finish
	public:
		LongRunObj(SynchornizedList *myList) : elements_(myList) {

		}
		void run(){
			for (int i =0; i < 4; i++) {
				elements_->addElement(i);
				sleep(1);
			}

		}
		~LongRunObj(){
			cout << " Destroying Long Run Obj " << this << endl;
		}
	private:
		SynchornizedList  *elements_;
};

TEST(ThreadTest, ThreadsRun){
	SynchornizedList *myList_;
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
	Thread *thread1 ;

	myList_ = new SynchornizedList();
	thread1 = new Thread(new RunnableObject(myList_));

	thread1->start();
	thread1->join();

	ASSERT_FALSE(thread1->isRunning());
	ASSERT_EQ(100, myList_->getSize());

	delete thread1;
	delete myList_;

}
/**
* For testing Thread.join we have the following test cases:
* 	1-Normal join is called before the thread starts
*   2-Normal join is called after the thread is started and before it finishes (Thread is running)
*   3-Normal join is called after the thread finishes
*  	4-Timed join is called before the thread starts
*   5-Timed join is called after the thread is started and before it finishes (Thread is running)
*   6-Timed join is called after the thread finishes
*   7-Timed join times out cause thread didn't finish execution and timeout reached
*
* The following TEST cases represent the previous ones respectively
*/

TEST(ThreadTest, ThreadsJoinable1){
	// Test of normal join is called before the thread starts

	SynchornizedList *myList_;
	Thread *thread1 ;

	myList_ = new SynchornizedList();
	thread1 = new Thread(new RunnableObject(myList_));

	thread1->join();

	ASSERT_FALSE(thread1->isRunning());
	ASSERT_EQ(0, myList_->getSize());

	delete thread1;
	delete myList_;

}

TEST(ThreadTest, ThreadsJoinable2){
//  Test of normal join is called after the thread is started and before it finishes (Thread is running)
	SynchornizedList *myList_;
	Runnable * runnable;
	Thread *thread1 ;

	myList_ = new SynchornizedList();
	thread1 = new Thread(new RunnableObject(myList_));

	thread1->start();
	// will make sure that you have the thread started already..
	usleep(10);
	thread1->join();
	ASSERT_FALSE(thread1->isRunning());
	ASSERT_EQ(100, myList_->getSize());

	delete thread1;
	delete myList_;

}

TEST(ThreadTest, ThreadsJoinable3){
//  Test of normal join is called after the thread finishes
	SynchornizedList *myList_;
	Thread *thread1 ;

	myList_ = new SynchornizedList();
	thread1 = new Thread(new RunnableObject(myList_));

	thread1->start();
	// will make sure that you have the thread started already..
	usleep(20);
	thread1->join();
	ASSERT_FALSE(thread1->isRunning());
	ASSERT_EQ(100, myList_->getSize());

	delete thread1;
	delete myList_;

}

TEST(ThreadTest, ThreadsJoinable4){
//  Test of timed join is called before the thread starts
	SynchornizedList *myList_;
	Runnable *runnable;
	Thread *thread1 ;

	myList_ = new SynchornizedList();
	thread1 = new Thread(new RunnableObject(myList_));

	thread1->join(3);

	ASSERT_FALSE(thread1->isRunning());
	ASSERT_EQ(0, myList_->getSize());

	delete thread1;
	delete myList_;

}

TEST(ThreadTest, ThreadsJoinable5){
//  Test of timed join is called after the thread is started and before it finishes (Thread is running)
	SynchornizedList *myList_;
	Thread *thread1 ;

	myList_ = new SynchornizedList();
	thread1 = new Thread(new RunnableObject(myList_));

	thread1->start();
	// will make sure that you have the thread started already..
	usleep(10);
	thread1->join(3);
	ASSERT_FALSE(thread1->isRunning());
	ASSERT_EQ(100, myList_->getSize());

	delete thread1;
	delete myList_;

}

TEST(ThreadTest, ThreadsJoinable6){
//  Test of timed join is called after the thread finishes
	SynchornizedList *myList_;
	Thread *thread1 ;

	myList_ = new SynchornizedList();
	thread1 = new Thread(new RunnableObject(myList_));

	thread1->start();
	// will make sure that you have the thread started already..
	usleep(20);
	thread1->join();
	ASSERT_FALSE(thread1->isRunning());
	ASSERT_EQ(100, myList_->getSize());

	delete thread1;
	delete myList_;

}

TEST(ThreadTest, ThreadsJoinable7){
//  Test of timed join times out cause thread didn't finish execution and timeout reached
	SynchornizedList *myList_;
	Thread *thread1 ;
	myList_ = new SynchornizedList();
	thread1 = new Thread(new LongRunObj(myList_));

	thread1->start();
	/*struct timespec currentTime;
	clock_gettime(CLOCK_REALTIME,&currentTime);
	cout << "Current time " << currentTime.tv_sec << endl;*/
	usleep(50);
	ASSERT_THROW(thread1->join(1), TimeOutException);
	/*clock_gettime(CLOCK_REALTIME,&currentTime);
	cout << "Current time " << currentTime.tv_sec << endl;*/
	ASSERT_TRUE(thread1->isRunning());
	thread1->join();
	cout << "ThreadsJoinable7: Deleting thread1 & myList_" << endl;
	delete thread1;
	cout << "ThreadsJoinable7: Deleted thread1" << endl;
	cout << "ThreadsJoinable7: Deleting myList_ " << myList_ << endl;
	delete myList_;
	cout << "ThreadsJoinable7: Deleted myList_" << endl;

}
TEST(ThreadTest, ThreadsStartAfterJoin){
	SynchornizedList *myList_;
	Thread *thread1 ;

	myList_ = new SynchornizedList();
	thread1 = new Thread(new RunnableObject(myList_));

	thread1->join(3);
	thread1->start();
	thread1->join();
	ASSERT_EQ(100, myList_->getSize());

	delete thread1;
	delete myList_;

}

TEST(ThreadTest, ThreadsRestartingFails){
	SynchornizedList *myList_;
	Thread *thread1 ;

	myList_ = new SynchornizedList();
	thread1 = new Thread(new RunnableObject(myList_));

	thread1->start();
	thread1->join();
	ASSERT_THROW(thread1->start(), AlreadyStartedException);

	delete thread1;
	delete myList_;

}
/**
 * Now we need to test the following:
 * 1- Canceling a thread state=Enabled/type=ASYNC
 * 2- Canceling a thread state=Enabled/type=Deffered then join
 * 3- Canceling a thread state=Disabled
 * 4- Canceling a thread state=Enabled/type=ASYNC with a cleanup method
 * 5- Creating a detached thread and making sure we cannot join it
 * 6- Creating a detached thread and trying to re-detach
 * 7- Creating a joinable thread and trying to detach it
 */

TEST(ThreadTest, CancelThread1){

	SynchornizedList *myList_;
	Thread *thread1 ;

	myList_ = new SynchornizedList();
	thread1 = new Thread(new LongRunObj(myList_));

	thread1->start();
	usleep(50);
	thread1->cancel();
	ASSERT_LT(myList_->getSize(),2);
	thread1->join();

	delete thread1;
	delete myList_;

}

TEST(ThreadTest, CancelThread2){

	SynchornizedList *myList_;
	Thread *thread1 ;

	myList_ = new SynchornizedList();
	thread1 = new Thread(new LongRunObj(myList_), true, CANCEL_DEFERRED);
	cout << "Created Thread" << endl;
	thread1->start();
	cout << "Started Thread" << endl;
	usleep(50);
	thread1->cancel();
	cout << "Canceled Thread" << endl;
	ASSERT_LT(myList_->getSize(),2);
	thread1->join(); //Block until thread terminates to ensure clean destruction

	delete thread1;
	delete myList_;
}
