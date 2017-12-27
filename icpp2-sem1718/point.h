#ifndef _POINT_H
#define _POINT_H

#include "interfaces.h"

// smazte tento radek po implementaci tridy Point
// jinak nebudou spousteny testy pro tridu Point
#define POINT_NOT_IMPLEMENTED

// ...
// zde chybi deklarace tridy Point
// ...

class Point : public APoint {
private:
	int row, column;

public:
	//Point();
	// Vytvori bod na zadanem radku a sloupci
	Point(int row, int column);
	// Zrusi bod
	~Point();

	// Vraci souradnici radek bodu
	int getRow() const override;
	// Vraci souradnici sloupce bodu
	int getColumn() const override;

	// Test primeho kontaktu
	// Vraci true - pokud se dva body tesne dotykaji
	// Vraci falce - pokud this == point
	bool isInContact(const APoint& point) const override;

	// Vraci true, pokud souradnice this a point jsou shodne
	bool operator==(const APoint& point) const override;
	// Vraci true, pokud souradnice this a point nejsou shodne
	bool operator!=(const APoint& point) const override;

};

#endif