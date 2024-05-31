#pragma once

#include "IProposal.h"
#include "Employee.h"
#include "Book.h"
#include "Double.h"

class BookProposal : public IProposal {
private:
	Employee* _employee;
	Book* _book;

public:
	BookProposal();
	BookProposal(Employee*, Book*);
	BookProposal(Employee*, Object*);
	~BookProposal();

public:
	Employee* getEmployee() override {
		return _employee;
	}
	Object* getSponsoredLocation() override {
		return dynamic_cast<Object*>(_book);
	}

	Double getTotalAmount() override;
	std::string toString() override {
		return "BookProposal";
	}
};