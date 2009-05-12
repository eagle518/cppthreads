#include <gtest/gtest.h>
#include <time.h>
#include "Semaphore.h"

namespace cppthreads {
	TEST(SemaphoreTest, testWait)	{
		Semaphore sem;
		ASSERT_EQ(0, sem.getValue());
		sem.signal();
		sem.wait();
		ASSERT_EQ(0, sem.getValue());
	}

	TEST(SemaphoreTest, testConstructWithValue)	{
		int32_t value = 3;
		Semaphore sem(value);
		ASSERT_EQ(value, sem.getValue());
		sem.wait();
		sem.wait();
		sem.wait();
		ASSERT_EQ(0, sem.getValue());
	}

	TEST(SemaphoreTest, testTryWait)	{

		Semaphore sem;
		ASSERT_EQ(0, sem.getValue());
		ASSERT_EQ(false, sem.tryWait());
		sem.signal();
		ASSERT_EQ(true, sem.tryWait());
		ASSERT_EQ(false, sem.tryWait());
	}
	TEST(SemaphoreTest, testTryTimedWait1)	{
		Semaphore sem;
		ASSERT_EQ(0, sem.getValue());
		ASSERT_EQ(false, sem.wait(5));
		sem.signal();
		ASSERT_EQ(true, sem.wait(5));
	}

}
