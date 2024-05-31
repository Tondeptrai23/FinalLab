#include "TourParser.h"
#include "Utils.h"

Object* TourParser::parse(std::string line) {
	std::vector<std::string> tokens = Utils::String::split(line, ", ");

	std::string destination = Utils::String::split(tokens[0], "=")[1];
	std::string cost = Utils::String::split(tokens[1], "=")[1].substr(1);
	std::string link = tokens[2].substr(5);

	Object* tour = new Tour(destination, Double(stod(cost)), link);
	return tour;
}

