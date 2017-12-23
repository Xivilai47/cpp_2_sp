#ifndef _TILE_H
#define _TILE_H

#include "defines.h"
#include "interfaces.h"
#include "point.h"

// smazte tento radek po implementaci tridy Tile
// jinak nebudou spousteny testy pro tridu Tile
#define TILE_NOT_IMPLEMENTED

// ...
// zde chybi deklarace tridy Tile
// ...

class Tile : public ATile {
private:
	Point position;													// TODO - zeptat se Piskana
	TileState tileState;
	int bombsInNeighbourhood;
	bool bombTile;

public:
	// Vytvori bunku na zadane souradnici
	// Neni bombou, nema bomby v okoli, bunka je skryta
	Tile(const Point& position);

	// Zrusi bunku
	~Tile();

	// Vraci polohu bunky
	const Point& getPosition() const;
	// Nastavi novou polohu bunky
	void setPosition(const Point& position);

	// Vraci pocet bomb v okoli bunky
	int getBombsInNeighbourhood() const;
	// Nastavi pocet bomb v okoli bunky
	void setBombsInNeighbourhood(int bombsInNeighbourhood);

	// Vraci true, pokud je na bunce bomba
	bool isBombTile() const;
	// Nastavi jestli je na bunce bomba
	void setBombTile(bool bombTile);

	// Vraci stav bunky
	TileState getTileState() const;
	// Nastavi stav bunky
	void setTileState(TileState tileState);

};

#endif