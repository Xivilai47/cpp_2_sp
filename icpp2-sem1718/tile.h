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
	APoint& position;
	TileState tileState;
	int bombsInNeighbourhood;
	bool bombTile;

public:
	// Vytvori bunku na zadane souradnici
	// Neni bombou, nema bomby v okoli, bunka je skryta
	Tile(const APoint& position);

	// Zrusi bunku
	~Tile();

	// Vraci polohu bunky
	const APoint& getPosition() const override;
	// Nastavi novou polohu bunky
	void setPosition(const APoint& position) override;

	// Vraci pocet bomb v okoli bunky
	int getBombsInNeighbourhood() const override;
	// Nastavi pocet bomb v okoli bunky
	void setBombsInNeighbourhood(int bombsInNeighbourhood) override;

	// Vraci true, pokud je na bunce bomba
	bool isBombTile() const override;
	// Nastavi jestli je na bunce bomba
	void setBombTile(bool bombTile) override;

	// Vraci stav bunky
	TileState getTileState() const override;
	// Nastavi stav bunky
	void setTileState(TileState tileState) override;

};

#endif