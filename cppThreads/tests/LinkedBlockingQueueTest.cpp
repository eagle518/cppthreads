#include <gtest/gtest.h>
#include "BlockingQueue.h"
#include "LinkedBlockingQueue.h"
#include "DummyObject.h"
#include "OutOfSpaceException.h"
#include <iostream>

namespace cppthreads {
	TEST(LinkedBlockingQueue, AddTest) {

		BlockingQueue *queue1 = new LinkedBlockingQueue(5);
		ASSERT_TRUE(queue1->add(new DummyObject(1)));
		ASSERT_TRUE(queue1->add(new DummyObject(2)));
		ASSERT_TRUE(queue1->add(new DummyObject(3)));
		ASSERT_TRUE(queue1->add(new DummyObject(4)));
		ASSERT_TRUE(queue1->add(new DummyObject(5)));
		SuperObject *dummy1 = new DummyObject(6);
		ASSERT_THROW(queue1->add(dummy1), OutOfSpaceException);
		delete queue1;
		delete dummy1;

		BlockingQueue *queue2 = new LinkedBlockingQueue();
		for (int i=0; i< 1000; i++) {
			ASSERT_TRUE(queue2->add(new DummyObject(1)));
		}
		ASSERT_TRUE(queue2->remainingCapacity() == BlockingQueue::MAX_VALUE);
		ASSERT_TRUE(queue2->getCapacity() == BlockingQueue::MAX_VALUE);
		delete queue2;
	}

	TEST(LinkedBlockingQueue, OfferTest) {

		BlockingQueue *queue = new LinkedBlockingQueue(5);
		ASSERT_TRUE(queue->offer(new DummyObject(1)));
		ASSERT_TRUE(queue->offer(new DummyObject(2)));
		ASSERT_TRUE(queue->offer(new DummyObject(3)));
		ASSERT_TRUE(queue->offer(new DummyObject(4)));
		ASSERT_TRUE(queue->offer(new DummyObject(5)));
		SuperObject *dummy1 = new DummyObject(6);
		ASSERT_FALSE(queue->offer(dummy1, 3));
		ASSERT_FALSE(queue->offer(dummy1));
		delete queue;
		delete dummy1;
	}

	TEST(LinkedBlockingQueue, MixedTest) {
		BlockingQueue *queue = new LinkedBlockingQueue(5);
		SuperObject *dummy1 = new DummyObject(1);
		ASSERT_TRUE(queue->offer(dummy1));
		ASSERT_TRUE(queue->offer(new DummyObject(2)));
		ASSERT_TRUE(queue->offer(new DummyObject(3)));
		ASSERT_TRUE(queue->offer(new DummyObject(4)));
		ASSERT_TRUE(queue->add(new DummyObject(5)));
		ASSERT_EQ(5, queue->size());
		SuperObject *tmp1 = queue->take();
		ASSERT_EQ(dummy1, tmp1);
		ASSERT_EQ(4, queue->size());
		delete tmp1;
		SuperObject *tmp2 = queue->element();
		ASSERT_EQ(4, queue->size());
		ASSERT_TRUE(tmp2 != NULL);

		delete queue->take();
		ASSERT_EQ(3, queue->size());
		delete queue->take();
		ASSERT_EQ(2, queue->size());
		delete queue->take();
		ASSERT_EQ(1, queue->size());
		SuperObject *tmp3 = queue->poll(3);
		ASSERT_TRUE(tmp3 != NULL);
		if (tmp3 != NULL) {
			delete tmp3;
		}
		ASSERT_EQ(0, queue->size());
		ASSERT_EQ(NULL, queue->poll(3));
		ASSERT_EQ(NULL, queue->element());

		delete queue;
	}
}
