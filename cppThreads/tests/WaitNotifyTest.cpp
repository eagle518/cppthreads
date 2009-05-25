#include "DummyObject.h"
#include "ThreadingException.h"
#include "Thread.h"
#include <gtest/gtest.h>
#include <iostream>

using namespace cppthreads;
using namespace std;

static uint16_t refCount_ = 0;

class DummyWaiter : public Runnable {
public:
	DummyWaiter(DummyObject* obj) : obj_(obj) {}
	
	void run() { 
		cout << "Waiting..." << endl;
		cout << ++refCount_ << endl;
		obj_->wait(); 
	}
private:
	DummyObject* obj_;
};

class DummyTimedWaiter : public Runnable {
public:
	DummyTimedWaiter(DummyObject* obj, uint32_t timeOut) : 
		obj_(obj), timeOut_(timeOut) {}
	void run() { 
		cout << "Waiting for " << timeOut_ << " seconds..." << endl;
		++refCount_;
		obj_->wait(timeOut_);
	}
private:
	uint32_t timeOut_;
	DummyObject* obj_;
};

class DummyNotifier :  public Runnable {
public:
	DummyNotifier(DummyObject* obj) : obj_(obj) {}
	void run() {
		cout << "Notifying Threads..." << endl; 
		obj_->notify();
		--refCount_; 
	}
private:
	DummyObject* obj_;
};

class DummyGroupNotifier : public Runnable {
public:
	DummyGroupNotifier(DummyObject* obj) : obj_(obj) {}
	void run() {
		cout << "Notifiying All Threads..." << endl; 
		obj_->notifyAll();
		refCount_ = 0;
	}
private:
	DummyObject* obj_;
};

class WaitNotifyTest : public ::testing::Test {
protected:
	DummyObject* object;
	DummyWaiter* dummyWaiter;
	DummyTimedWaiter* dummyTimedWaiter;
	DummyNotifier* dummyNotifier;
	DummyGroupNotifier* dummyGroupNotifier;
	
	virtual void SetUp() {
		object = new DummyObject(1);
		dummyWaiter = new DummyWaiter(object);
		dummyTimedWaiter = new DummyTimedWaiter(object,1);
		dummyNotifier = new DummyNotifier(object);
		dummyGroupNotifier = new DummyGroupNotifier(object);
	}

	virtual void TearDown() {
		delete object;
	}
};

TEST_F(WaitNotifyTest, testTimedWait) {
	Thread* thread1 = new Thread(dummyTimedWaiter);
	time_t t0 = time(NULL);
	refCount_ = 0;
	thread1->start();
	thread1->join();
	ASSERT_EQ(refCount_, 1);
	time_t t1 = time(NULL);
	EXPECT_EQ(t1 - t0, 1);
	delete thread1;
}

TEST_F(WaitNotifyTest, testNotifyNoWait) {
	Thread* thread1 = new Thread(dummyNotifier);
	refCount_ = 0;
	thread1->start();
	thread1->join();
	ASSERT_EQ(refCount_, 0xffff);
	delete thread1;
}

/* We need some sort of way to explicitly terminate threads for this
 * test to work */

/*TEST_F(WaitNotifyTest, testNotifyAllWait) {
	Thread* thread1 = new Thread(dummyWaiter);
	Thread* thread2 = new Thread(dummyWaiter);
	Thread* thread3 = new Thread(dummyWaiter);
	Thread* thread4 = new Thread(dummyNotifier);
	Thread* thread5 = new Thread(dummyGroupNotifier);
	refCount_ = 0;

	thread1->start();
	thread2->start();
	thread3->start();
	ASSERT_EQ(refCount_, 3);
	thread4->start();
	thread4->join();
	ASSERT_EQ(refCount_, 2);
	thread5->start();
	thread5->join();
	ASSERT_EQ(refCount_, 0);
	thread1->kill();
	thread2->kill();
	thread3->kill();
	delete thread1;
	delete thread2;
	delete thread3;
	delete thread4;
	delete thread5;
}*/
