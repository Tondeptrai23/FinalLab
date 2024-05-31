#pragma once

#include "Object.h"
#include "Integer.h"

class NumberFormat : public Object {
private:
	std::string _decimalSeparator;
	std::string _thousandsSeparator;
	int _precision;

public:
	NumberFormat() {
		_decimalSeparator = ".";
		_thousandsSeparator = ",";
		_precision = 2;
	}

	NumberFormat(std::string thousandsSeparator) {
		_decimalSeparator = ".";
		_thousandsSeparator = thousandsSeparator;
		_precision = 2;
	}

	NumberFormat(std::string decimalSeparator, std::string thousandsSeparator, int precision) {
		_decimalSeparator = decimalSeparator;
		_thousandsSeparator = thousandsSeparator;
		_precision = precision;
	}

	std::string decimalSeparator() {
		return _decimalSeparator;
	}

	std::string thousandsSeparator() {
		return _thousandsSeparator;
	}

	std::string toString() override {
		return "NumberFormat";
	}
};