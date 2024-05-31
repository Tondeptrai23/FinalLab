#pragma once

#include "Object.h"
#include "Double.h"

class Tour : public Object {
private:
	std::string _destination;
	Double _cost;
	std::string _link;

public:
	Tour();
	Tour(std::string destination, Double cost, std::string link);

public:
	std::string getDestination();
	Double getCost();
	std::string getLink();

	std::string toString() override {
		return "Tour";
	}
};