#pragma once

#include "IProposal.h"
#include "Employee.h"
#include "Tour.h"

class TourProposal : public IProposal {
private:
	Employee* _employee;
	Tour* _tour;

public:
	TourProposal();
	TourProposal(Employee*, Tour*);
	TourProposal(Employee*, Object*);
	~TourProposal();
public:
	Employee* getEmployee() override {
		return _employee;
	}
	Object* getSponsoredLocation() override {
		return dynamic_cast<Object*>(_tour);
	}

	Double getTotalAmount() override;
	std::string toString() override {
		return "TourProposal";
	}
};