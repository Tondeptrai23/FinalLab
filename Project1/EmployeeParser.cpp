#include "EmployeeParser.h"

#include "Utils.h"


Object* EmployeeParser::parse(std::string data) {
	std::vector<std::string> tokens = Utils::String::split(data, ", ");

	std::string name = Utils::String::split(tokens[0], "=")[1];
	std::string email = Utils::String::split(tokens[1], "=")[1];
	std::string startDate = Utils::String::split(tokens[2], "=")[1];
	
	Object* emp = new Employee(name, email, Date::parse(startDate));
	return emp;
}