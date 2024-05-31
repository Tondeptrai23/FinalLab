#pragma once

#include "TourProposal.h"
#include "TextDataProvider.h"

#include <vector>

/*
* From version 2, this class isn't used anymore, it's replaced by ProposalTextDataProvider
* This class is kept here for showing the changes between versions only
*/
class TourProposalTextDataProvider : public TextDataProvider{
public:
	TourProposalTextDataProvider() : TextDataProvider() {};
	TourProposalTextDataProvider(std::string fileName) : TextDataProvider(fileName) {};

public:
	std::vector<TourProposal*> getProposals();

	std::string toString() override {
		return "ProposalTextDataProvider";
	}
};