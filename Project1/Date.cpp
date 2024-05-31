#include "Date.h"
#include "Utils.h"

#include <ctime>
#include <format>

Date::Date() {
	_day = _month = 1;
	_year = 1900;
}

Date::Date(int day, int month, int year) {
	_day = day;
	_month = month;
	_year = year;
}

Date Date::parse(std::string data) {
	std::vector<std::string> tokens = Utils::String::split(data, "/");

	int day = std::stoi(tokens[0]);
	int month = std::stoi(tokens[1]);
	int year = std::stoi(tokens[2]);

	return Date(day, month, year);

}

Date Date::getToday() {
	time_t info = time(NULL);
	tm now;
	localtime_s(&now, &info);

	int day = now.tm_mday;
	int month = now.tm_mon + 1;
	int year = now.tm_year + 1900;

	return Date(day, month, year);
}

Double Date::getYearsToToday() {
	Date today = Date::getToday();
	int yearDiff = today._year - this->_year;
	int monthDiff = 0;

	if (today._month < this->_month) {
		yearDiff--;
		monthDiff = today._month + 12 - this->_month;
	}
	else if (today._month == this->_month) {
		monthDiff = 0;
	}
	else {
		monthDiff = today._month - this->_month;
	}

	double result = yearDiff + static_cast<double>(monthDiff) / 12;
	return Double(result);
}

std::string Date::getFormattedDate() {
	return std::format("{}/{}/{}", _day, _month, _year);
}