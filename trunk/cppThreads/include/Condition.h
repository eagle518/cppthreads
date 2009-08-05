#ifndef CONDITION_H
#define CONDITION_H
#include <pthread.h>
#include "SuperObject.h"
#include "Mutex.h"

namespace cppthreads {
	class Condition : public SuperObject {
		public:
			Condition(Mutex& mutex);
			
			virtual void await();
			virtual bool await(uint32_t timeOut);
			virtual void signal();
			virtual void signalAll();
			virtual pthread_cond_t getConditionHandle() { return conditionHandle_; }
			virtual Mutex getMutex() { return mutex_; }

			virtual ~Condition();
		private:
			pthread_cond_t conditionHandle_;
			Mutex mutex_;
	};
}
#endif /* CONDITION_H */
