#pragma once

#include "Object.h"

class IParsable : public Object {
public:
	virtual Object* parse(std::string line) = 0;

	std::string toString() override {
		return "IParsable";
	}
};