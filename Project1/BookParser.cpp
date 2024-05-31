#include "BookParser.h"
#include "Utils.h"
#include "Book.h"
#include "Double.h"

Object* BookParser::parse(std::string data) {
	std::vector<std::string> tokens = Utils::String::split(data, ", ");

	std::string title = Utils::String::split(tokens[0], "=")[1];
	std::string price = Utils::String::split(tokens[1], "=")[1].substr(1);
	std::string link = tokens[2].substr(5);

	Object* book = new Book(title, Double(stod(price)), link);
	return book;
}