#include "TourProposalToTableConverter.h"
#include "Employee.h"
#include "Date.h"
#include "TableFormat.h"
#include "ProposalTextDataProvider.h"
#include "TourProposal.h"
#include "Factory.h"
#include "IParsable.h"
#include "EmployeeParser.h"
#include "TourParser.h"
#include "Policy.h"
#include "ProposalToTableConverter.h"
#include "BookParser.h"
#include "ProposalFactory.h"
#include "BookProposal.h"
#include "TourProposalTextDataProvider.h"
#include "ProposalManager.h"
#include "DoubleToCurrencyConverter.h"

#include <iostream>

void config() {
	Policy::getInstance()->registerWith({ 0, 2 }, "Fresher", 35);
	Policy::getInstance()->registerWith({ 2, 3 }, "Junior", 45);
	Policy::getInstance()->registerWith({ 3, 4 }, "Middle", 60);
	Policy::getInstance()->registerWith({ 4, 20 }, "Senior", 75);

	Factory<IParsable*>::getInstance()->registerWith("Employee", new EmployeeParser());
	Factory<IParsable*>::getInstance()->registerWith("Tour", new TourParser());
	Factory<IParsable*>::getInstance()->registerWith("Book", new BookParser());

	// This seems to be over-engineered, i dont know any alternatives way to do this...
	ProposalFactory::getInstance()->registerWith("Tour", [](Employee* employee, Object* tour) {
		return new TourProposal(employee, dynamic_cast<Tour*>(tour));
		});
	ProposalFactory::getInstance()->registerWith("Book", [](Employee* employee, Object* book) {
		return new BookProposal(employee, dynamic_cast<Book*>(book));
		});
}


int main() {
	config();
	std::string filename = "MixedProposal.txt";
	ProposalTextDataProvider provider(filename);
	ProposalManager manager(provider.getProposals());

	std::vector<std::string> headers = { "STT", "Name", "Classifcation", "OfferName", "Price", "Support", "Amount" };
	std::vector<int> columnSizes = { 3, 20, 14, 20, 15, 10, 13 };
	TableFormat tableConfig3(headers, columnSizes, "|");
	ProposalToTableConverter converter(tableConfig3);

	std::cout << "Version 3 of Employee Sponsor Counting:" << std::endl;
	std::cout << "Found " << manager.size() << " proposals." << std::endl;
	std::cout << converter.convert(manager.getProposals()) << std::endl;

	DoubleToCurrencyConverter currencyConverter(CurrencyFormat(",", "$", 0));
	Double totalFunds = manager.calculateTotalFunds();
	std::cout << "Total amount of all proposals: " <<
		currencyConverter.convert(dynamic_cast<Object*>(&totalFunds)) << std::endl;
	std::cout << std::endl;



	std::cout << "Testing Table Converter Job";
	std::cout << std::endl;

	filename = "TourProposal.txt";
	TourProposalTextDataProvider provider2(filename);
	std::vector<TourProposal*> proposals2 = provider2.getProposals();

	std::vector<std::string> headers2 = { "STT", "Name","Email", "Classifcation", "Destination", "Price", "Support", "Amount" };
	std::vector<int> columnSizes2 = { 5, 18, 14,14, 12, 15, 10, 11 };
	TableFormat tableConfig2(headers2, columnSizes2, "|");
	TourProposalToTableConverter converter2(tableConfig2);

	std::cout << "Version 2 of Employee Sponsor Counting:" << std::endl;
	std::cout << "Found " << proposals2.size() << " proposals." << std::endl;
	std::cout << converter2.convert(proposals2) << std::endl;

	double total = 0.0f;
	for (auto proposal : proposals2) {
		total += proposal->getTotalAmount().getValue();
		delete proposal;
	}
	std::cout << "Total amount of all proposals: " << total << std::endl;


	return 0;
}



