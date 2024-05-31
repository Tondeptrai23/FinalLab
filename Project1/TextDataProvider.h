#pragma once

#include "Object.h"

#include <fstream>
#include <iostream>

class TextDataProvider : public Object {
protected:
	std::string _fileName;
	std::ifstream _input;

protected:
	TextDataProvider() {
		_fileName = "data.txt";
		_input.open(_fileName);
	}

	TextDataProvider(std::string fileName) {
		_fileName = fileName;
		_input.open(_fileName);
	}

	~TextDataProvider() {
		_input.close();
	}

	void open(std::string fileName) {
		_input.close();
		_input.open(fileName);
	}

	void close() {
		_input.close();
	}

	std::string toString() override {
		return "TextDataProvider";
	}
};