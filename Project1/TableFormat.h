#pragma once

#include "Object.h"
#include <vector>

class TableFormat : public Object {
private:
	std::vector<std::string> _headers;
	std::vector<int> _columnSizes;
	std::string _separator;
	std::string _columnFormat;

public:
	TableFormat() {
		_headers = std::vector<std::string>();
		_columnSizes = std::vector<int>();
		_separator = "|";
		_columnFormat = "{{:<{}}}";
	}

	TableFormat(std::vector<std::string> headers, std::vector<int> columnSizes, std::string separator) {
		_headers = headers;
		_columnSizes = columnSizes;
		_separator = separator;
		_columnFormat = " {{:<{}}} ";
	}

	std::vector<std::string> headers(){
		return _headers;
	}

	std::vector<int> columnSizes() {
		return _columnSizes;
	}

	std::string separator() {
		return _separator;
	}

	std::string columnFormat() {
		return _columnFormat;
	}

	std::string toString() override {
		return "TableFormat";
	}

};