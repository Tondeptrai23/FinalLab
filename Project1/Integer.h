#pragma once

#include "Object.h"

class Integer : public Object {
private:
	int _value;

public:
	Integer() : _value(0) {}
	Integer(int value) : _value(value) {}

	int getValue() {
		return _value;
	}

	void setValue(int value) {
		_value = value;
	}

	std::string toString() override {
		return "Integer";
	}
};