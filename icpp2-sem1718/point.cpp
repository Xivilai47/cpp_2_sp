#include "point.h"

// ...
// zde chybi definice tridy Point
// ...

Point::Point(int row, int column) : APoint(row, column), row(row), column(column) {

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
bool Point::isInContact(const APoint& point) const {
	if (point == *this) {
		return false;
	}
	if (point.getRow() >= this->row - 1 && point.getRow() <= this->row + 1 &&
		point.getColumn() >= this->column - 1 && point.getColumn() <= this->column + 1) {
		return true;
	}
	return false;
}

// Vraci true, pokud souradnice this a point jsou shodne
bool Point::operator==(const APoint& point) const {
	if (point.getRow() == this->row && point.getColumn() == this->column) {
		return true;
	}
	return false;
}
// Vraci true, pokud souradnice this a point nejsou shodne
bool Point::operator!=(const APoint& point) const {
	if (point.getRow() != this->row || point.getColumn() != this->column) {
		return true;
	}
	return false;
}
