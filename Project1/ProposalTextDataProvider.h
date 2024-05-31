#pragma once

#include "IProposal.h"
#include "TextDataProvider.h"

#include <vector>

class ProposalTextDataProvider : public TextDataProvider {
public:
	ProposalTextDataProvider() : TextDataProvider() {};
	ProposalTextDataProvider(std::string fileName) : TextDataProvider(fileName) {};

public:
	std::vector<IProposal*> getProposals();

	std::string toString() override {
		return "ProposalTextDataProvider";
	}
};