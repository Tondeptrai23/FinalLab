#pragma once

#include "Object.h"

#include <vector>

class CurrencyFormat : public Object {
private:
	std::vector<std::string> _currencyPositiveFormat = { "$n", "n$", "$ n", "n $" };

private:
	std::string _currencyThousandSeparator;
	std::string _currencySymbol;
	int _currencyPositive;

public:
	CurrencyFormat() {
		_currencyThousandSeparator = ".";
		_currencySymbol = "$";
		_currencyPositive = 0;
	}

	CurrencyFormat(std::string currencyThousandSeparator, std::string currencySymbol, int currencyPositive) {
		_currencyThousandSeparator = currencyThousandSeparator;
		_currencySymbol = currencySymbol;
		if (currencyPositive < 0 || currencyPositive > 3) {
			_currencyPositive = 0;
		}
		_currencyPositive = currencyPositive;
	}

	std::string currencyThousandSeparator() {
		return _currencyThousandSeparator;
	}

	std::string currencySymbol() {
		return _currencySymbol;
	}

	std::string currencyPositiveFormat() {
		return _currencyPositiveFormat[_currencyPositive];
	}

	std::string toString() override {
		return "CurrencyFormat";
	}
};