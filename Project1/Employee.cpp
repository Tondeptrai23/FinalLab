#include "Employee.h"
#include "Policy.h"

Employee::Employee() {
	_email = _name = "";
	_startDate = Date();
}

Employee::Employee(std::string name, std::string email, Date date) {
	_name = name;
	_email = email;
	_startDate = date;
}


Employee::Employee(std::string name, std::string email, int startDay, int startMonth, int startYear) {
	_name = name;
	_email = email;
	_startDate = Date(startDay, startMonth, startYear);
}

std::string Employee::getName() {
	return _name;
}

std::string Employee::getEmail() {
	return _email;
}

Date Employee::getStartDate() {
	return _startDate;
}

Double Employee::getYearsOfExperience() {
	return _startDate.getYearsToToday();
}
