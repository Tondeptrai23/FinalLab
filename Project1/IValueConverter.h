#pragma once

#include "Object.h"

class IValueConverter : public Object {
public:
	virtual std::string convert(Object* object) = 0;
};