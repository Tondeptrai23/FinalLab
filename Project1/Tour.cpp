#include "Tour.h"

Tour::Tour() {
	_destination = "";
	_cost = Double(0.0);
	_link = "";
}

Tour::Tour(std::string destination, Double cost, std::string link) {
	_destination = destination;
	_cost = cost;
	_link = link;
}

Double Tour::getCost() {
	return _cost;
}

std::string Tour::getDestination() {
	return _destination;
}

std::string Tour::getLink() {
	return _link;
}




