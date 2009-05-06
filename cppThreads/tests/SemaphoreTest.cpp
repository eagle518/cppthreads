#include <gtest/gtest.h>
#include "Semaphore.h"

namespace cppthreads {
	TEST(SemaphoreTest, testWait)	{
		Semaphore sem;
		ASSERT_EQ(0, sem.getValue());
	}
}
