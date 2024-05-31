#include "ProposalTextDataProvider.h"
#include "Utils.h"
#include "IParsable.h"
#include "Factory.h"
#include "TourProposal.h"
#include "BookProposal.h"
#include "ProposalFactory.h"

#include <sstream>

std::vector<IProposal*> ProposalTextDataProvider::getProposals() {
	std::vector<IProposal*> proposals;
	std::string firstLine = "";
	std::string secondLine = "";

	while (!_input.eof()) {
		getline(_input, firstLine);
		getline(_input, secondLine);

		// Skip the empty line
		std::string temp = "";
		getline(_input, temp);

		// Read 1st line
		std::vector<std::string> employeeTokens = Utils::String::split(firstLine, ": ");
		
		// Read 2nd line
		std::string sponsoredLocationType = "";
		std::string sponsoredLocationData = "";
		std::istringstream iss(secondLine);
		getline(iss, sponsoredLocationType, ' '); //Skip "=>"
		getline(iss, sponsoredLocationType, ':');
		getline(iss, sponsoredLocationData);

		IParsable* employeeParser = Factory<IParsable*>::getInstance()->create(employeeTokens[0]);
		IParsable* sponsoredParser = Factory<IParsable*>::getInstance()->create(sponsoredLocationType);

		if (employeeParser == nullptr || sponsoredParser == nullptr) {
			continue;
		}

		Employee* employee = dynamic_cast<Employee*>(employeeParser->parse(employeeTokens[1]));
		Object* sponsoredLocation = dynamic_cast<Object*>(sponsoredParser->parse(sponsoredLocationData));

		IProposal* proposal = nullptr;
		
		proposal = ProposalFactory::getInstance()->create(sponsoredLocationType, employee, sponsoredLocation);
		proposals.push_back(proposal);
	}
	return proposals;
}