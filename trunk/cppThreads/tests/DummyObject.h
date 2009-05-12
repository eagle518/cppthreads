#ifndef DUMMYOBJECT_H_
#define DUMMYOBJECT_H_

#include "SuperObject.h"

class DummyObject: public SuperObject {
	public:
		DummyObject(int32_t data) : data_(data) {}
		int32_t getData() { return data_ ;}
		virtual const char *toString() const {
			std::stringstream stream;
			stream << data_;
			return stream.str().c_str();
		}
		virtual ~DummyObject(){}
	private:
		int32_t data_;
};

#endif /* DUMMYOBJECT_H_ */
