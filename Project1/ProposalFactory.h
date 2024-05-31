#pragma once

#include "IProposal.h"
#include "Employee.h"
#include "Object.h"
#include <functional>

#include <map>

class ProposalFactory : public Object {
private:
	inline static ProposalFactory* _instance = nullptr;
	std::map<std::string, std::function<IProposal* (Employee*, Object*)>> _proposals;

private:
	ProposalFactory() {}

public:
	static ProposalFactory* getInstance() {
		if (_instance == nullptr) {
			_instance = new ProposalFactory();
		}
		return _instance;
	}

	void registerWith(std::string name, std::function<IProposal*(Employee*, Object*)> proposalCreatingFunc) {
		_proposals.insert({ name, proposalCreatingFunc });
	}

	IProposal* create(std::string type, Employee* employee, Object* sponsoredLocation) {
		IProposal* proposal = _proposals[type](employee, sponsoredLocation);
		return proposal;
	}

	std::string toString() override {
		return "ProposalFactory";
	}
};