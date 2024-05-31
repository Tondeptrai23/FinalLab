#pragma once

#include "TableConverter.h"
#include "TourProposal.h"
#include "Policy.h"
#include "DoubleToCurrencyConverter.h"
#include "IntegerToPercentageConverter.h"

#include <iostream>

class TourProposalToTableConverter : public TableConverter<TourProposal*> {
public:
	TourProposalToTableConverter() : TableConverter<TourProposal*>() {}
	TourProposalToTableConverter(TableFormat config) :TableConverter<TourProposal*>(config) {}

	std::string toString() override {
		return "TourProposalToTableConverter";
	}
};


std::vector<std::string> TourProposalToTableConverter::RowConverter::setRowData(TourProposal* item) {
	DoubleToCurrencyConverter converter(CurrencyFormat(",", "$", 0));
	IntegerToPercentageConverter percentConverter(NumberFormat(","));
	Policy* policy = Policy::getInstance();
	Employee* employee = item->getEmployee();
	Tour* tour = dynamic_cast<Tour*>(item->getSponsoredLocation());
	

	std::string index = std::to_string(_index++);

	std::string name = employee->getName();

	std::string email = employee->getEmail();

	std::string classification = policy->getClassification(employee->getYearsOfExperience());

	std::string destination = tour->getDestination();

	Double cost = tour->getCost();
	std::string costString = converter.convert(dynamic_cast<Object*>(&cost));

	Integer percentOfSponsorship = policy->getPercentOfSponsorship(employee->getYearsOfExperience());
	std::string percentString = percentConverter.convert(dynamic_cast<Object*>(&percentOfSponsorship));

	Double total = item->getTotalAmount();
	std::string totalString = converter.convert(dynamic_cast<Object*>(&total));


	std::vector<std::string> result = {
		index, name, email, classification,destination, costString, percentString, totalString
	};

	return result;
}

