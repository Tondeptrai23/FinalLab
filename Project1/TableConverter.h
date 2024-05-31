#pragma once
#pragma once

#include "IValueConverter.h"
#include "TableFormat.h"

#include <vector>
#include <format>
#include <tuple>

template <class T>
class TableConverter : public Object {
protected:
	TableFormat _config;

protected:
	TableConverter();
	TableConverter(TableFormat config);
	std::tuple<std::string, std::vector<std::string>> prepareTableStructure();

public:
	std::string convert(std::vector<T> data);

	std::string toString() override {
		return "TableConverter";
	}

protected:
	class RowConverter : public Object {
	protected:
		std::vector<std::string> _columnFormats;
		int _index = 1;
		std::vector<int> _columnSizes;
		std::vector<std::string> _rowData;

	public:
		virtual std::vector<std::string> setRowData(T data) { return {}; };
		
		RowConverter() {
			//
		}
		RowConverter(std::vector<std::string> columnFormats, std::vector<int> columnSizes) {
			this->_columnFormats = columnFormats;
			this->_columnSizes = columnSizes;
		}

		std::string convert(T data);
		std::string toString() override {
			return "RowConverter";
		}
	};
};

template <class T>
TableConverter<T>::TableConverter() {
	//
}

template <class T>
TableConverter<T>::TableConverter(TableFormat config) {
	// Column sizes should be at least the size of the headers
	for (int i = 0; i < config.headers().size(); i++) {
		if (config.headers()[i].size() > config.columnSizes()[i]) {
			config.columnSizes()[i] = config.headers()[i].size();
		}
	}

	_config = config;
}

template <class T>
std::tuple<std::string, std::vector<std::string>> TableConverter<T>::prepareTableStructure() {
	std::vector<std::string> columnFormats;
	std::string titles = "";
	int tableWidth = 0;

	for (int i = 0; i < _config.columnSizes().size(); i++) {
		std::string currentColumnFormat = std::vformat(_config.columnFormat(), std::make_format_args(_config.columnSizes()[i]));

		titles += _config.separator() + std::vformat(currentColumnFormat, std::make_format_args(_config.headers()[i]));
		if (i == _config.columnSizes().size() - 1) {
			currentColumnFormat += _config.separator();
			titles += _config.separator();
		}

		columnFormats.push_back(_config.separator() + currentColumnFormat);
		tableWidth += _config.columnSizes()[i] + 2;
	}

	std::string headers = "";
	headers += titles + "\n";
	headers += std::string(tableWidth + _config.columnSizes().size(), '-') + "\n";

	return std::make_tuple(headers, columnFormats);
}

template <class T>
std::string TableConverter<T>::convert(std::vector<T> items) {
	std::tuple preprocessed = prepareTableStructure();

	std::string result = std::get<0>(preprocessed);
	std::vector<std::string> columnFormats = std::get<1>(preprocessed);

	RowConverter rowConverter(columnFormats, _config.columnSizes());
	for (T item : items) {
		std::string row = rowConverter.convert(item);
		result += row + "\n";
	}
	return result;
}

template <class T>
std::string TableConverter<T>::RowConverter::convert(T item) {
	_rowData = setRowData(item);

	// Overflow data truncation
	for (int i = 0; i < _rowData.size(); i++) {
		if (_rowData[i].size() > _columnSizes[i]) {
			_rowData[i] = _rowData[i].substr(0, _columnSizes[i] - 3) + "...";
		}
	}

	std::string result = "";
	for (int i = 0; i < _rowData.size(); i++) {
		result += std::vformat(_columnFormats[i], std::make_format_args(_rowData[i]));
	}
	return result;
}