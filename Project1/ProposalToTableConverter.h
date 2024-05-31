#pragma once

#include "TableConverter.h"
#include "IProposal.h"
#include "Tour.h"
#include "Book.h"
#include "Policy.h"
#include "DoubleToCurrencyConverter.h"
#include "IntegerToPercentageConverter.h"

class ProposalToTableConverter : public TableConverter<IProposal*> {
public:
	ProposalToTableConverter() : TableConverter<IProposal*>() {}
	ProposalToTableConverter(TableFormat config) :TableConverter<IProposal*>(config) {}

	std::string toString() override {
		return "ProposalToTableConverter";
	}
};

std::vector<std::string> ProposalToTableConverter::RowConverter::setRowData(IProposal* item) {
	std::vector<std::string> result;
	DoubleToCurrencyConverter converter(CurrencyFormat(",", "$", 2));
	IntegerToPercentageConverter percentConverter(NumberFormat(","));

	Employee* employee = item->getEmployee();
	Policy* policy = Policy::getInstance();

	// common data
	std::string index = std::to_string(_index++);

	std::string name = employee->getName();

	std::string classification = policy->getClassification(employee->getYearsOfExperience());

	Integer percentOfSponsorship = policy->getPercentOfSponsorship(employee->getYearsOfExperience());
	std::string percentString = percentConverter.convert(dynamic_cast<Object*>(&percentOfSponsorship));	

	Double total = item->getTotalAmount();
	std::string totalString = converter.convert(dynamic_cast<Object*>(&total));

	
	// private data
	if (item->toString() == "TourProposal") {
		Tour* tour = dynamic_cast<Tour*>(item->getSponsoredLocation());

		std::string destination = tour->getDestination();
		Double cost = tour->getCost();
		std::string costString = converter.convert(dynamic_cast<Object*>(&cost));

		result = {
			index, name, classification, destination, costString, percentString, totalString
		};
	}

	else if (item->toString() == "BookProposal") {
		Employee* employee = item->getEmployee();
		Book* book = dynamic_cast<Book*>(item->getSponsoredLocation());

		std::string title = book->getTitle();
		Double price = book->getPrice();
		std::string priceString = converter.convert(dynamic_cast<Object*>(&price));

		result = {
			index, name, classification, title, priceString, percentString, totalString
		};
	}
	return result;
}
