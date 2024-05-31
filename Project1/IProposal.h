#pragma once

#include "Employee.h"

class IProposal : public Object{
public:
	virtual Employee* getEmployee() = 0;
	virtual Object* getSponsoredLocation() = 0;
	virtual Double getTotalAmount() = 0;
};