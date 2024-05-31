#include "TourProposalTextDataProvider.h"

#include "IParsable.h"
#include "Utils.h"
#include "Factory.h"

std::vector<TourProposal*> TourProposalTextDataProvider::getProposals() {
	std::vector<TourProposal*> proposals;
	std::string firstLine = "";
	std::string secondLine = "";

	while (!_input.eof()) {
		getline(_input, firstLine);
		getline(_input, secondLine);

		// Skip the empty line
		std::string temp = "";
		getline(_input, temp);

		std::vector<std::string> employeeTokens = Utils::String::split(firstLine, ": ");
		std::vector<std::string> sponsoredLocationTokens = Utils::String::split(secondLine, ": ");
		std::string sponsoredLocationType = sponsoredLocationTokens[0].substr(3);

		IParsable* employeeParser = Factory<IParsable*>::getInstance()->create(employeeTokens[0]);
		IParsable* sponsorsedLocationParser = Factory<IParsable*>::getInstance()->create(sponsoredLocationType);

		if (employeeParser == nullptr || sponsorsedLocationParser == nullptr) {
			continue;
		}

		Employee* employee = dynamic_cast<Employee*>(employeeParser->parse(employeeTokens[1]));
		Tour* sponsoredLocation = dynamic_cast<Tour*>(sponsorsedLocationParser->parse(sponsoredLocationTokens[1]));

		TourProposal* proposal = new TourProposal(employee, sponsoredLocation);
		proposals.push_back(proposal);
	}
	return proposals;
}