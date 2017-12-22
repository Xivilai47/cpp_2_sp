#ifndef _INTERFACES_H
#define _INTERFACES_H

//  ===============================
//  === NEMENIT OBSAH SOUBORU ! ===
//  ===============================

#include "defines.h"
#include <vector>

// Bod - souradnice v hracim planu
struct APoint {

	// Vytvori bod na zadanem radku a sloupci
	APoint(int row, int column);
	// Zrusi bod
	virtual ~APoint();

	// Vraci souradnici radek bodu
	virtual int getRow() const = 0;
	// Vraci souradnici sloupce bodu
	virtual int getColumn() const = 0;

	// Test primeho kontaktu
	// Vraci true - pokud se dva body tesne dotykaji
	// Vraci falce - pokud this == point
	virtual bool isInContact(const APoint& point) const = 0;

	// Vraci true, pokud souradnice this a point jsou shodne
	virtual bool operator==(const APoint& point) const=0;
	// Vraci true, pokud souradnice this a point nejsou shodne
	virtual bool operator!=(const APoint& point) const=0;

};

// Bunka - jedna bunka herniho pole
struct ATile {
	
	// Vytvori bunku na zadane souradnici
	// Neni bombou, nema bomby v okoli, bunka je skryta
	ATile(const APoint& position);
	
	// Zrusi bunku
	virtual ~ATile();

	// Vraci polohu bunky
	virtual const APoint& getPosition() const = 0;
	// Nastavi novou polohu bunky
	virtual void setPosition(const APoint& position) = 0;

	// Vraci pocet bomb v okoli bunky
	virtual int getBombsInNeighbourhood() const = 0;
	// Nastavi pocet bomb v okoli bunky
	virtual void setBombsInNeighbourhood(int bombsInNeighbourhood) = 0;

	// Vraci true, pokud je na bunce bomba
	virtual bool isBombTile() const = 0;
	// Nastavi jestli je na bunce bomba
	virtual void setBombTile(bool bombTile) = 0;
	
	// Vraci stav bunky
	virtual TileState getTileState() const = 0;
	// Nastavi stav bunky
	virtual void setTileState(TileState tileState) = 0;

};

// Typ sousedstvi bunek - skupina bunek primo se dotykajici dane bunky
typedef std::vector<ATile*> TileNeighbourhood;

// Mapa
struct AMap {

protected:
	// pocet radku herniho pole (souradnice y)
	const int rows;
	// pocet sloupecku herniho pole (souradnice x)
	const int columns;
	// celkovy pocet min na hernim poli
	const int totalMines;

public:
	// Vytvori prazdnou mapu
	AMap(int rows, int columns, int mines);

	// Zrusi mapu
	virtual ~AMap();

	// Vrati vybranou bunku
	virtual ATile& getTile(const APoint& point) = 0;
	// Vrati vybranou bunku
	virtual ATile& getTile(int row, int column) = 0;
	// Vrati vybranou bunku
	virtual const ATile& getTile(const APoint& point) const = 0;
	// Vrati vybranou bunku
	virtual const ATile& getTile(int row, int column) const = 0;

	// Nastavi na dane bunce hodnoty dle vstupniho parametru
	// Metoda je pouzita pro moznost otestovani hry
	virtual void setTile(const ATile& tile) = 0;

	// Prepocita vsechny hodnoty "bombsInNeighbourhood" na jednotlivych bunkach
	virtual void resetBombsInNeighbourhood() = 0;

	// Vygeneruje nahodne mapu, umisti na ni "totalMines" min a nastavi jednotliva policka
	virtual void generateMap() = 0;

	// Vrati okoli bunky (bunky primo sousedici s danou bunkou)
	virtual TileNeighbourhood getNeighbourhood(const APoint& point) = 0;

	// Vrati true, pokud je na dane bunce umistena libovolna vlajka
	virtual bool isAnyFlagOnPoint(const APoint& point) const = 0;

	// Oznaci danou bunku vlajkou "bomba"
	virtual void flagPoint(const APoint& point) = 0;

	// Oznaci danou bunku vlajkou "neznamo"
	virtual void flagAsUnknownPoint(const APoint& point) = 0;

	// Zrusi vlajky na dane bunce
	virtual void unflagPoint(const APoint& point) = 0;

	// Odkryje bunku
	// A pokud splnuje, ze nema zadne bomby v okoli, odkryvani pokracuje na vsechny
	// sousedici bunky; proces se opakuje dokud odkryta bunka splnuje podminku 
	// getBombsInNeighbourhood() == 0
	virtual void uncoverPoint(const APoint& point) = 0;

	// Vrati pocet umistenych vlajek typu bomba
	virtual int getCountOfBombFlags() const = 0;

	// Vrati novy herni stav
	// Pokud hrac odkryl bunku s bombou -> prohra
	// Pokud zbyva odkryt bunek co je bomb -> vyhra
	// Pokud hra oznacil vlajkou "bomba" vsechny bomby a zadnou bunku navic -> vyhra
	// Jinak hra pokracuje normalne dal
	virtual GameState getNewGameState() const = 0;

	// == nasledujici metody jsou jiz implementovane a pro vas nepotrebne a nezajimave ==

	// Vykreslovani mapy do konzole
	void render() const;

	// Prevede znak na cislo
	static char getLetterForNumber(int number);
	// Prevede cislo na znak
	static int getNumberForLetter(char letter);
};

#endif
