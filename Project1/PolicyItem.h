#pragma once

#include "Object.h"
#include "Integer.h"

#include <vector>

class PolicyItem :public Object {
private:
	std::pair<int, int> _rangeYearsOfWork;
	std::string _classification;
	int _percentOfSponsoring;
public:
	PolicyItem() {
		_percentOfSponsoring = 0;
		_classification = "";
		_rangeYearsOfWork = std::pair<int, int>(0, 0);
	}

	PolicyItem(std::pair<int, int> rangeYearsOfWork, std::string classification, int percentOfSponsoring) {
		_rangeYearsOfWork = rangeYearsOfWork;
		_classification = classification;
		_percentOfSponsoring = percentOfSponsoring;
	}

	std::pair<int, int> getRangeYearsOfWork() {
		return _rangeYearsOfWork;
	}

	std::string getClassification() {
		return _classification;
	}

	Integer getPercentOfSponsoring() {
		return Integer(_percentOfSponsoring);
	}

	std::string toString() override {
		return "PolicyItem";
	}
};