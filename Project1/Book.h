#pragma once

#include "Object.h"
#include "Double.h"

class Book : public Object {
private:
	std::string _title;
	Double _price;
	std::string _link;

public:
	Book();
	Book(std::string title, Double price, std::string link);

public:
	std::string getTitle();
	Double getPrice();
	std::string getLink();

	std::string toString() override {
		return "Book";
	}
};