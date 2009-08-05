#include <gtest/gtest.h>
#include "BlockingQueue.h"
#include "ArrayBlockingQueue.h"
#include "DummyObject.h"
#include "OutOfSpaceException.h"
#include <iostream>

namespace cppthreads {
	TEST(ArrayBlockingQueue, AddTest)
	{

		BlockingQueue *queue1 = new ArrayBlockingQueue(5);
		ASSERT_TRUE(queue1->add(new DummyObject(1)));
		ASSERT_TRUE(queue1->add(new DummyObject(2)));
		ASSERT_TRUE(queue1->add(new DummyObject(3)));
		ASSERT_TRUE(queue1->add(new DummyObject(4)));
		ASSERT_TRUE(queue1->add(new DummyObject(5)));
		SuperObject *dummy1 = new DummyObject(6);
		ASSERT_THROW(queue1->add(dummy1), OutOfSpaceException);
		delete queue1;
		delete dummy1;

		BlockingQueue *queue2 = new ArrayBlockingQueue();
		for (int i=0; i< 1000; i++) {
			ASSERT_TRUE(queue2->add(new DummyObject(1)));
		}
		ASSERT_TRUE(queue2->remainingCapacity() == BlockingQueue::MAX_VALUE);
		ASSERT_TRUE(queue2->getCapacity() == BlockingQueue::MAX_VALUE);
		delete queue2;
	}

	TEST(ArrayBlockingQueue, OfferTest) {

		BlockingQueue *queue = new ArrayBlockingQueue(5);
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

	TEST(ArrayBlockingQueue, OrderingTest) {
		BlockingQueue *queue = new ArrayBlockingQueue();
		ASSERT_TRUE(queue->offer(new DummyObject(1)));
		ASSERT_TRUE(queue->offer(new DummyObject(2)));
		ASSERT_TRUE(queue->offer(new DummyObject(3)));
		DummyObject *ret1 = dynamic_cast<DummyObject *>(queue->take());
		ASSERT_TRUE(ret1 != NULL);
		ASSERT_EQ(1, ret1->getData());
		delete ret1;
		DummyObject *ret2 = dynamic_cast<DummyObject *>(queue->take());
		ASSERT_TRUE(ret2 != NULL);
		ASSERT_EQ(2, ret2->getData());
		delete ret2;

		ASSERT_TRUE(queue->offer(new DummyObject(4)));

		DummyObject *ret3 = dynamic_cast<DummyObject *>(queue->take());
		ASSERT_TRUE(ret3 != NULL);
		ASSERT_EQ(3, ret3->getData());
		delete ret3;

		DummyObject *ret4 = dynamic_cast<DummyObject *>(queue->take());
		ASSERT_TRUE(ret4 != NULL);
		ASSERT_EQ(4, ret4->getData());
		delete ret4;
		ASSERT_EQ(0, queue->size());
		delete queue;
	}
	TEST(ArrayBlockingQueue, PeekAndRemoveTest) {

		BlockingQueue *queue = new ArrayBlockingQueue();
		SuperObject *dummy1 = new DummyObject(1);
		ASSERT_TRUE(queue->offer(dummy1));
		ASSERT_EQ(dummy1, queue->peek());

		ASSERT_TRUE(queue->contains(dummy1));
		ASSERT_TRUE(queue->remove(dummy1));
		ASSERT_FALSE(queue->remove(dummy1));
		ASSERT_FALSE(queue->contains(dummy1));
		ASSERT_EQ(0, queue->size());

		delete queue;
		delete dummy1;
	}

	TEST(ArrayBlockingQueue, MixedTest) {
		BlockingQueue *queue = new ArrayBlockingQueue(5);
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
		SuperObject *tmp2 = queue->peek();
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
		ASSERT_EQ(NULL, queue->peek());

		delete queue;
	}
}
