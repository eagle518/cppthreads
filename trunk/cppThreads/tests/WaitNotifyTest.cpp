#include "DummyObject.h"
#include "ThreadingException.h"
#include "Thread.h"
#include "Mutex.h"
#include <gtest/gtest.h>
#include <iostream>

using namespace cppthreads;
using namespace std;

static uint16_t refCount_ = 0;
static Mutex m;

class DummyWaiter : public Runnable {
public:
	DummyWaiter(DummyObject* obj) : obj_(obj) {}
	
	void run() {
		cout << "Waiting..." << endl;
		m.lock();
		++refCount_;
		m.unlock();
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
		m.lock();
		++refCount_;
		m.unlock();
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
		m.lock();
		if(refCount_ > 0)
			--refCount_;
		m.unlock(); 
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
		m.lock();
		refCount_ = 0;
		m.unlock();
	}
private:
	DummyObject* obj_;
};

class WaitNotifyTest : public ::testing::Test {
protected:
	DummyObject* object;
	
	virtual void SetUp() {
		object = new DummyObject(1);
	}

	virtual void TearDown() {
		delete object;
	}
};

TEST_F(WaitNotifyTest, testTimedWait) {
	Thread* thread = new Thread(new DummyTimedWaiter(object, 1));
	refCount_ = 0;
	thread->start();
	thread->join();
	ASSERT_EQ(refCount_, 1);
	delete thread;
}

TEST_F(WaitNotifyTest, testNotifyNoWait) {
	Thread* thread = new Thread(new DummyNotifier(object));
	refCount_ = 1;
	thread->start();
	thread->join();
	ASSERT_EQ(refCount_, 0);
	delete thread;
}

TEST_F(WaitNotifyTest, testNotifyWait) {
	Thread* waiter1 = new Thread(new DummyWaiter(object));
	Thread* waiter2 = new Thread(new DummyTimedWaiter(object,2));
	Thread* notifier1 = new Thread(new DummyNotifier(object));
	Thread* notifier2 = new Thread(new DummyGroupNotifier(object));
	refCount_ = 0;
	waiter1->start();
	ASSERT_EQ(refCount_, 1);
	waiter2->start();
	ASSERT_EQ(refCount_, 2);
	notifier1->start();
	notifier1->join();
	ASSERT_EQ(refCount_, 1);
	notifier2->start();
	notifier2->join();
	ASSERT_EQ(refCount_, 0);
	waiter1->join();
	waiter2->join();
	delete notifier1;
	delete notifier2;
	delete waiter1;
	delete waiter2;
}
