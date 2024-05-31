#pragma once

#include "Object.h"
#include "Date.h"
#include "Double.h"

class Employee : public Object {
private:
	std::string _name;
	std::string _email;
	Date _startDate;

public:
	Employee();
	Employee(std::string name, std::string email, Date date);
	Employee(std::string name, std::string email, int day, int month, int year);

public:
	std::string getName();
	std::string getEmail();
	Date getStartDate();
	Double getYearsOfExperience();

	std::string toString() override {
		return "Employee";
	}
};


