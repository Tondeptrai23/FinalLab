#pragma once

#include "Object.h"
#include "PolicyItem.h"
#include "Double.h"
#include "Integer.h"

#include <vector>

class Policy : public Object {
private:
	std::vector<PolicyItem> _policyItems;
	inline static Policy* _instance = nullptr;

private:
	Policy();

public:
	static Policy* getInstance();
	void registerWith(std::pair<int, int> yearsOfWork, std::string classification, int percentOfSponsoring);
	void flush();

	Integer getPercentOfSponsorship(Double yearsOfWork);
	std::string getClassification(Double yearsOfWork);

	std::string toString() override {
		return "Policy";
	}
};