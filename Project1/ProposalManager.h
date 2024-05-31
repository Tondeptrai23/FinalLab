#pragma once

#include "Object.h"
#include "IProposal.h"
#include "Double.h"

#include <vector>

class ProposalManager : public Object {
private:
	std::vector<IProposal*> _proposals;

public:
	ProposalManager() {
		_proposals = std::vector<IProposal*>();
	}

	ProposalManager(std::vector<IProposal*> proposals) {
		_proposals = proposals;
	}

	~ProposalManager() {
		for (IProposal* proposal : _proposals) {
			delete proposal->getEmployee();
			delete proposal->getSponsoredLocation();
			delete proposal;
		}
	}

public:
	std::vector<IProposal*> getProposals() {
		return _proposals;
	}

	Double calculateTotalFunds() {
		double total = 0.0f;
		for (IProposal* proposal : _proposals) {
			total += proposal->getTotalAmount().getValue();
		}
		return Double(total);
	}

	int size() {
		return _proposals.size();
	}

	std::string toString() override {
		return "ProposalManager";
	}
};
