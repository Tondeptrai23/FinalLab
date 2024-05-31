#pragma once

#include "Object.h"
#include "IValueConverter.h"

class Double : public Object {
private:
	double _value;

public:
	Double() : _value(0) {}
	Double(double value) : _value(value) {}

	double getValue() {
		return _value;
	}

	void setValue(double value) {
		_value = value;
	}

	std::string toString() override {
		return "Double";
	}
};