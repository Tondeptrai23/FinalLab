#pragma once

#include "Employee.h"
#include "IParsable.h"

class EmployeeParser : public IParsable {
public:
	Object* parse(std::string data) override;

	std::string toString() override {
		return "EmployeeParser";
	}
};