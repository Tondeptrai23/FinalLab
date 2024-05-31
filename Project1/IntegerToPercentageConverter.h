#pragma once

#include "IValueConverter.h"
#include "NumberFormat.h"

class IntegerToPercentageConverter : public IValueConverter {
private:
	NumberFormat _info;

public:
	IntegerToPercentageConverter();
	IntegerToPercentageConverter(NumberFormat info);
	std::string convert(Object* object) override;

	std::string toString() override {
		return "IntegerToPercentageConverter";
	}
};