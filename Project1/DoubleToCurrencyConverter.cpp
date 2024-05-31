#include "DoubleToCurrencyConverter.h"

#include <format>
#include <regex>

DoubleToCurrencyConverter::DoubleToCurrencyConverter() {
	_info = CurrencyFormat();
}

DoubleToCurrencyConverter::DoubleToCurrencyConverter(CurrencyFormat info) {
	_info = info;
}

std::string DoubleToCurrencyConverter::convert(Object* object) {
	Double* d = dynamic_cast<Double*>(object);
	double doubleValue = std::round(d->getValue() * 100) / 100;

	std::string numberPart = std::format("{}", static_cast<int>(doubleValue));
	std::string decimalPart = std::format("{:.2f}", doubleValue - static_cast<int>(doubleValue)).substr(2);

	for (int i = numberPart.size() - 1, count = 1; i >= 1; i--, count++) {
		if (count % 3 == 0) {
			numberPart.insert(i, _info.currencyThousandSeparator());
		}
	}

	std::string format = _info.currencyPositiveFormat();
	std::string symbol = _info.currencySymbol();

	std::string result = numberPart + "." + decimalPart;
	result = std::regex_replace(format, std::regex("n"), result);
	std::string result2 = std::regex_replace(result, std::regex("\\$"), symbol);

	return result2;
}