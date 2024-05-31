#include "Book.h"

Book::Book() {
	_title = "";
	_price = Double(0.0);
	_link = "";
}

Book::Book(std::string title, Double price, std::string link) {
	_title = title;
	_price = price;
	_link = link;
}

std::string Book::getTitle() {
	return _title;
}

Double Book::getPrice() {
	return _price;
}

std::string Book::getLink() {
	return _link;
}

