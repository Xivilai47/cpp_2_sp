#ifndef _MAP_H
#define _MAP_H

#include "interfaces.h" 
#include "point.h"
#include "tile.h"

// smazte tento radek po implementaci tridy Map
// jinak nebudou spousteny testy pro tridu Map
#define MAP_NOT_IMPLEMENTED

// ...
// zde chybi deklarace tridy Map
// ...

class Map : AMap {
protected:
	// pocet radku herniho pole (souradnice y)
	const int rows;
	// pocet sloupecku herniho pole (souradnice x)
	const int columns;
	// celkovy pocet min na hernim poli
	const int totalMines;

public:
	// Vytvori prazdnou mapu
	Map(int rows, int columns, int mines)/* : rows(rows),columns(columns),totalMines(mines)*/;

	// Zrusi mapu
	~Map();

	// Vrati vybranou bunku
	ATile& getTile(const APoint& point);
	// Vrati vybranou bunku
	ATile& getTile(int row, int column);
	// Vrati vybranou bunku
	const ATile& getTile(const APoint& point) const;
	// Vrati vybranou bunku
	const ATile& getTile(int row, int column) const;

	// Nastavi na dane bunce hodnoty dle vstupniho parametru
	// Metoda je pouzita pro moznost otestovani hry
	void setTile(const ATile& tile);

	// Prepocita vsechny hodnoty "bombsInNeighbourhood" na jednotlivych bunkach
	void resetBombsInNeighbourhood();

	// Vygeneruje nahodne mapu, umisti na ni "totalMines" min a nastavi jednotliva policka
	void generateMap();

	// Vrati okoli bunky (bunky primo sousedici s danou bunkou)
	TileNeighbourhood getNeighbourhood(const APoint& point);

	// Vrati true, pokud je na dane bunce umistena libovolna vlajka
	bool isAnyFlagOnPoint(const APoint& point) const;

	// Oznaci danou bunku vlajkou "bomba"
	void flagPoint(const APoint& point);

	// Oznaci danou bunku vlajkou "neznamo"
	void flagAsUnknownPoint(const APoint& point);

	// Zrusi vlajky na dane bunce
	void unflagPoint(const APoint& point);

	// Odkryje bunku
	// A pokud splnuje, ze nema zadne bomby v okoli, odkryvani pokracuje na vsechny
	// sousedici bunky; proces se opakuje dokud odkryta bunka splnuje podminku 
	// getBombsInNeighbourhood() == 0
	void uncoverPoint(const APoint& point);

	// Vrati pocet umistenych vlajek typu bomba
	int getCountOfBombFlags() const;

	// Vrati novy herni stav
	// Pokud hrac odkryl bunku s bombou -> prohra
	// Pokud zbyva odkryt bunek co je bomb -> vyhra
	// Pokud hra oznacil vlajkou "bomba" vsechny bomby a zadnou bunku navic -> vyhra
	// Jinak hra pokracuje normalne dal
	GameState getNewGameState() const;

	//// == nasledujici metody jsou jiz implementovane a pro vas nepotrebne a nezajimave ==

	//// Vykreslovani mapy do konzole
	//void render() const;

	//// Prevede znak na cislo
	//static char getLetterForNumber(int number);
	//// Prevede cislo na znak
	//static int getNumberForLetter(char letter);
};

#endif