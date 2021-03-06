#include "tile.h"

// ...
// zde chybi definice tridy Tile
// ...

// Vytvori bunku na zadane souradnici
// Neni bombou, nema bomby v okoli, bunka je skryta
Tile::Tile(const APoint& position) : ATile(position), position(position.getRow(),position.getColumn()) {
	this->bombTile = false;
	this->bombsInNeighbourhood = 0;
	this->tileState = TileState::Hidden;
}

// Zrusi bunku
Tile::~Tile() {

}

// Vraci polohu bunky
const APoint& Tile::getPosition() const {
	return position;
}

// Nastavi novou polohu bunky
void Tile::setPosition(const APoint& position) {
	this->position = Point{ position.getRow(),position.getColumn() };
}

// Vraci pocet bomb v okoli bunky
int Tile::getBombsInNeighbourhood() const {
	return bombsInNeighbourhood;
}

// Nastavi pocet bomb v okoli bunky
void Tile::setBombsInNeighbourhood(int bombsInNeighbourhood) {
	this->bombsInNeighbourhood = bombsInNeighbourhood;
}

// Vraci true, pokud je na bunce bomba
bool Tile::isBombTile() const {
	return bombTile;
}
// Nastavi jestli je na bunce bomba
void Tile::setBombTile(bool bombTile) {
	this->bombTile = bombTile;
}

// Vraci stav bunky
TileState Tile::getTileState() const {
	return tileState;
}
// Nastavi stav bunky
void Tile::setTileState(TileState tileState) {
	this->tileState = tileState;
}

