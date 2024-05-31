#pragma once

#include "IValueConverter.h"
#include "CurrencyFormat.h"
#include "Double.h"

class DoubleToCurrencyConverter : public IValueConverter {
private:
	CurrencyFormat _info;

public:
	DoubleToCurrencyConverter();
	DoubleToCurrencyConverter(CurrencyFormat info);

public:
	std::string convert(Object* object) override;
	std::string toString() override {
		return "DoubleToCurrencyConverter";
	}
};