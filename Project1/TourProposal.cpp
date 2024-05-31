#include "TourProposal.h"

#include "Policy.h"

TourProposal::TourProposal() {
	_employee = nullptr;
	_tour = nullptr;
}

TourProposal::TourProposal(Employee* em, Tour* tour) {
	_employee = em;
	_tour = tour;
}

TourProposal::TourProposal(Employee* em, Object* tour) {
	_employee = em;
	_tour = dynamic_cast<Tour*>(tour);
}

TourProposal::~TourProposal() {
	delete _employee;
	delete _tour;
}


Double TourProposal::getTotalAmount() {
	double yearsOfExpience = _employee->getYearsOfExperience().getValue();

	double result = _tour->getCost().getValue();
	int percentOfSponsorship = Policy::getInstance()->getPercentOfSponsorship(yearsOfExpience).getValue();
	result *= (double)percentOfSponsorship / 100;
	return Double(result);

}
