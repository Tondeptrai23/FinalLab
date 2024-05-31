#include "Policy.h"

Policy::Policy() {
	_policyItems = std::vector<PolicyItem>();
}

Policy* Policy::getInstance() {
	if (_instance == nullptr) {
		_instance = new Policy();
	}
	return _instance;
}

void Policy::registerWith(std::pair<int, int> yearsOfWork, std::string classification, int percentOfSponsoring) {
	_policyItems.push_back(PolicyItem(yearsOfWork, classification, percentOfSponsoring));
}

Integer Policy::getPercentOfSponsorship(Double yearsOfWork) {
	double temp = yearsOfWork.getValue();

	for (PolicyItem policyItem : _policyItems) {
		std::pair<int, int> range = policyItem.getRangeYearsOfWork();
		if (temp >= range.first && temp < range.second) {
			return Integer(policyItem.getPercentOfSponsoring());
		}
	}

	return 0;
}

std::string Policy::getClassification(Double yearsOfWork) {
	double temp = yearsOfWork.getValue();

	for (PolicyItem policyItem : _policyItems) {
		std::pair<int, int> range = policyItem.getRangeYearsOfWork();
		if (temp >= range.first && temp < range.second) {
			return policyItem.getClassification();
		}
	}

	return "";
}

void Policy::flush() {
	_policyItems.clear();
}