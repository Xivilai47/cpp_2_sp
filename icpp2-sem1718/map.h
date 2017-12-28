#ifndef _MAP_H
#define _MAP_H

#include <vector>
#include <algorithm>
#include <numeric>
#include <time.h>
#include "interfaces.h" 
#include "point.h"
#include "tile.h"

// smazte tento radek po implementaci tridy Map
// jinak nebudou spousteny testy pro tridu Map
#define MAP_NOT_IMPLEMENTED

// ...
// zde chybi deklarace tridy Map
// ...

class Map : public AMap {
protected:
	// pocet radku herniho pole (souradnice y)
	const int rows;
	// pocet sloupecku herniho pole (souradnice x)
	const int columns;
	// celkovy pocet min na hernim poli
	const int totalMines;

	// container pro uchovavani bunek (Tile)
	std::vector<ATile> tiles;

public:
	// Vytvori prazdnou mapu
	Map(int rows, int columns, int mines);

	// Zrusi mapu
	~Map();

	// Vrati vybranou bunku
	ATile& getTile(const APoint& point) override;
	// Vrati vybranou bunku
	ATile& getTile(int row, int column) override;
	// Vrati vybranou bunku
	const ATile& getTile(const APoint& point) const override;
	// Vrati vybranou bunku
	const ATile& getTile(int row, int column) const override;

	// Nastavi na dane bunce hodnoty dle vstupniho parametru
	// Metoda je pouzita pro moznost otestovani hry
	void setTile(const ATile& tile) override;

	// Prepocita vsechny hodnoty "bombsInNeighbourhood" na jednotlivych bunkach
	void resetBombsInNeighbourhood() override;

	// Vygeneruje nahodne mapu, umisti na ni "totalMines" min a nastavi jednotliva policka
	void generateMap() override;

	// Vrati okoli bunky (bunky primo sousedici s danou bunkou)
	TileNeighbourhood getNeighbourhood(const APoint& point) override;

	// Vrati true, pokud je na dane bunce umistena libovolna vlajka
	bool isAnyFlagOnPoint(const APoint& point) const override;

	// Oznaci danou bunku vlajkou "bomba"
	void flagPoint(const APoint& point) override;

	// Oznaci danou bunku vlajkou "neznamo"
	void flagAsUnknownPoint(const APoint& point) override;

	// Zrusi vlajky na dane bunce
	void unflagPoint(const APoint& point) override;

	// Odkryje bunku
	// A pokud splnuje, ze nema zadne bomby v okoli, odkryvani pokracuje na vsechny
	// sousedici bunky; proces se opakuje dokud odkryta bunka splnuje podminku 
	// getBombsInNeighbourhood() == 0
	void uncoverPoint(const APoint& point) override;

	// Vrati pocet umistenych vlajek typu bomba
	int getCountOfBombFlags() const override;

	// Vrati novy herni stav
	// Pokud hrac odkryl bunku s bombou -> prohra
	// Pokud zbyva odkryt bunek co je bomb -> vyhra
	// Pokud hra oznacil vlajkou "bomba" vsechny bomby a zadnou bunku navic -> vyhra
	// Jinak hra pokracuje normalne dal
	GameState getNewGameState() const override;

//	// == nasledujici metody jsou jiz implementovane a pro vas nepotrebne a nezajimave ==
//
//	// Vykreslovani mapy do konzole
//	void render() const;
//
//	// Prevede znak na cislo
//	static char getLetterForNumber(int number);
//	// Prevede cislo na znak
//	static int getNumberForLetter(char letter);
};

#endif