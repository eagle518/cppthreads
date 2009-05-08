/*
 * Thread.h
 *
 *  Created on: May 5, 2009
 *      Author: Abd4llA
 */

#ifndef RUNNABLE_H_
#define RUNNABLE_H_

#include<iostream>
#include "SuperObject.h"
using namespace std;

namespace cppthreads {

	class Runnable: public SuperObject {
		private:

		public:
			virtual void run() {
				cout << "You have to override this method" << endl;
			}
			virtual ~Runnable();
	};
}
#endif /* RUNNABLE_H_ */
