#include <gtest/gtest.h>
#include "ThreadingException.h"
#include <iostream>
#include <time.h>
#include "Mutex.h"

namespace cppthreads {
	TEST(MutexTest, testLock)
	{
		Mutex mut;
		ASSERT_FALSE(mut.isLocked());
		mut.lock();
		ASSERT_EQ(false, mut.lock(3));
		ASSERT_TRUE(mut.isLocked());
		mut.unlock();
		ASSERT_EQ(true, mut.lock(3));
		ASSERT_TRUE(mut.isLocked());
		mut.unlock();
		ASSERT_FALSE(mut.isLocked());
		mut.unlock();
		ASSERT_FALSE(mut.isLocked());
	}

}
