#pragma once

#include "IParsable.h"

class BookParser : public IParsable {
public:
	Object* parse(std::string data) override;

	std::string toString() override {
		return "BookParser";
	}
};