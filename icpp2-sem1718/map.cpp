#include "map.h"

// ...
// zde chybi definice tridy Map
// ...


Map::Map(int rows, int columns, int mines) : AMap(rows,columns,mines) {

}

Map::~Map() {

}

// Vrati vybranou bunku
Tile& Map::getTile(const Point& point) {
	
}
// Vrati vybranou bunku
Tile& Map::getTile(int row, int column) {

}
// Vrati vybranou bunku
const Tile& Map::getTile(const Point& point) const {

}
// Vrati vybranou bunku
const Tile& Map::getTile(int row, int column) const {

}

// Nastavi na dane bunce hodnoty dle vstupniho parametru
// Metoda je pouzita pro moznost otestovani hry
void Map::setTile(const Tile& tile) {

}

// Prepocita vsechny hodnoty "bombsInNeighbourhood" na jednotlivych bunkach
void Map::resetBombsInNeighbourhood() {

}

// Vygeneruje nahodne mapu, umisti na ni "totalMines" min a nastavi jednotliva policka
void Map::generateMap() {

}

// Vrati okoli bunky (bunky primo sousedici s danou bunkou)
TileNeighbourhood Map::getNeighbourhood(const Point& point) {

}

// Vrati true, pokud je na dane bunce umistena libovolna vlajka
bool Map::isAnyFlagOnPoint(const Point& point) const {

}

// Oznaci danou bunku vlajkou "bomba"
void Map::flagPoint(const Point& point) {

}

// Oznaci danou bunku vlajkou "neznamo"
void Map::flagAsUnknownPoint(const Point& point) {

}

// Zrusi vlajky na dane bunce
void Map::unflagPoint(const Point& point) {

}

// Odkryje bunku
// A pokud splnuje, ze nema zadne bomby v okoli, odkryvani pokracuje na vsechny
// sousedici bunky; proces se opakuje dokud odkryta bunka splnuje podminku 
// getBombsInNeighbourhood() == 0
void Map::uncoverPoint(const Point& point) {

}

// Vrati pocet umistenych vlajek typu bomba
int Map::getCountOfBombFlags() const {

}

// Vrati novy herni stav
// Pokud hrac odkryl bunku s bombou -> prohra
// Pokud zbyva odkryt bunek co je bomb -> vyhra
// Pokud hra oznacil vlajkou "bomba" vsechny bomby a zadnou bunku navic -> vyhra
// Jinak hra pokracuje normalne dal
GameState Map::getNewGameState() const {

}