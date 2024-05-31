#pragma once

#include "Tour.h"
#include "IParsable.h"

class TourParser : public IParsable {
public:
	Object* parse(std::string line) override;

	std::string toString() override {
		return "TourParser";
	}
};