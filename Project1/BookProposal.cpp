#include "BookProposal.h"

#include "Policy.h"

BookProposal::BookProposal() {
	_employee = nullptr;
	_book = nullptr;
}

BookProposal::BookProposal(Employee* em, Book* book) {
	_employee = em;
	_book = book;
}

BookProposal::BookProposal(Employee* em, Object* book) {
	_employee = em;
	_book = dynamic_cast<Book*>(book);
}

BookProposal::~BookProposal() {
	delete _employee;
	delete _book;
}

Double BookProposal::getTotalAmount() {
	double yearsOfExpience = _employee->getYearsOfExperience().getValue();

	double result = _book->getPrice().getValue();
	int percentOfSponsorship = Policy::getInstance()->getPercentOfSponsorship(yearsOfExpience).getValue();
	result *= (double)percentOfSponsorship / 100;
	return Double(result);

}
