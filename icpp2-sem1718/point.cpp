#include "point.h"

// ...
// zde chybi definice tridy Point
// ...

Point::Point() : APoint(1, 1) {
	this->row = 1;
	this->column = 1;
}

Point::Point(int row, int column) : APoint(row, column) {
	this->row = row;
	this->column = column;
}

Point::~Point() {
}

// Vraci souradnici radek bodu
int Point::getRow() const {
	return this->row;
}
// Vraci souradnici sloupce bodu
int Point::getColumn() const {
	return this->column;
}

// Test primeho kontaktu
// Vraci true - pokud se dva body tesne dotykaji
// Vraci falce - pokud this == point
bool Point::isInContact(const Point& point) const {
	if (point == *this) {																			//DONE - nahradit 'point == this' po definici operatoru
		return false;
	}
	if (point.row >= this->row - 1 && point.row <= this->row + 1 &&
		point.column >= this->column - 1 && point.column <= this->column + 1) {
		return true;
	}
	return false;
}

// Vraci true, pokud souradnice this a point jsou shodne
bool Point::operator==(const Point& point) const {
	if (point.row == this->row && point.column == this->column) {
		return true;
	}
	return false;
}
// Vraci true, pokud souradnice this a point nejsou shodne
bool Point::operator!=(const Point& point) const {
	if (point.row != this->row || point.column != this->column) {
		return true;
	}
	return false;
}
