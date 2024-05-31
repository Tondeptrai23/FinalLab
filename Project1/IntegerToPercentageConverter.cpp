#include "IntegerToPercentageConverter.h"
#include "Integer.h"

#include <format>

IntegerToPercentageConverter::IntegerToPercentageConverter() {
	_info = NumberFormat();
}

IntegerToPercentageConverter::IntegerToPercentageConverter(NumberFormat info) {
	_info = info;
}

std::string IntegerToPercentageConverter::convert(Object* object) {
	Integer* i = dynamic_cast<Integer*>(object);

	std::string value = std::format("{}", i->getValue());

	for (int i = value.size() - 1, count = 1; i >= 1; i--, count++) {
		if (count % 3 == 0) {
			value.insert(i, _info.thousandsSeparator());
		}
	}

	value += "%";
	return value;
}
