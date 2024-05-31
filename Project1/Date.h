#pragma once
#include "Object.h"
#include "Double.h"

class Date : public Object {
private:
	int _day;
	int _month;
	int _year;

public:
	Date();
	Date(int day, int month, int year);

public:
	static Date parse(std::string line);
	static Date getToday();

public:
	Double getYearsToToday();
	std::string toString() override {
		return "Date";
	}
	std::string getFormattedDate();

};

