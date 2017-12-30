#include "map.h"

// ...
// zde chybi definice tridy Map
// ...

// getCountOfBombFlags()
bool is_bomb_flag(const ATile& tile) {
	return tile.getTileState() == TileState::BombFlag;
}

// getNewGameState()
bool is_unknown_flag(const ATile& tile) {
	return tile.getTileState() == TileState::UnknownFlag;
}

bool is_uncovered_tile(const ATile& tile) {
	return tile.getTileState() == TileState::Uncovered;
}

bool is_bomb_uncovered(const ATile& tile) {
	if (tile.getTileState() == TileState::Uncovered && tile.isBombTile()) {
		return true;
	}
	return false;
}

// Vytvori prazdnou mapu
Map::Map(int rows, int columns, int mines) : AMap(rows,columns,mines), rows(rows), columns(columns), totalMines(mines) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			tiles.push_back(Tile{ Point{ i, j } });
		}
	}
}

// Zrusi mapu
Map::~Map() {

}

// Vrati vybranou bunku
ATile& Map::getTile(const APoint& point) {
	std::vector<Tile>::iterator iter = tiles.begin();
	while (iter != tiles.end()) {
		if ((*iter).getPosition() == point) {
			return *iter;
		}
		iter++;
	}
}

// Vrati vybranou bunku
ATile& Map::getTile(int row, int column) {
	std::vector<Tile>::iterator iter = tiles.begin();
	while (iter != tiles.end()) {
		if ((*iter).getPosition() == Point{ row,column }) {
			return *iter;
		}
		iter++;
	}
}

// Vrati vybranou bunku
const ATile& Map::getTile(const APoint& point) const {
	std::vector<Tile>::const_iterator c_iter = tiles.begin();
	while (c_iter != tiles.end()) {
		if ((*c_iter).getPosition() == point) {
			return *c_iter;
		}
		c_iter++;
	}
}

// Vrati vybranou bunku
const ATile& Map::getTile(int row, int column) const {
	std::vector<Tile>::const_iterator c_iter = tiles.begin();
	while (c_iter != tiles.end()) {
		if ((*c_iter).getPosition() == Point{ row,column }) {
			return *c_iter;
		}
		c_iter++;
	}
}

// Nastavi na dane bunce hodnoty dle vstupniho parametru
// Metoda je pouzita pro moznost otestovani hry
void Map::setTile(const ATile& tile) {
	ATile& reffedTile = getTile(tile.getPosition());
	reffedTile.setBombTile(tile.isBombTile());
	reffedTile.setBombsInNeighbourhood(tile.getBombsInNeighbourhood());
	reffedTile.setTileState(tile.getTileState());

	// volani resetBombsInNeighbourhood() pridano kvuli testum, ktere volaji setTile() a nasledne uncoverPoint().
	// hodnoty ktere resetBombsInNeighbourhood() doplni jsou treba pro spravnou funkcnost odhalovani bunek
	resetBombsInNeighbourhood();
}

// Prepocita vsechny hodnoty "bombsInNeighbourhood" na jednotlivych bunkach
void Map::resetBombsInNeighbourhood() {
	
	std::vector<Tile>::iterator iter = tiles.begin();
	while (iter != tiles.end()) {
		int bombCount = 0;
			std::vector<ATile*> neighbourhood = getNeighbourhood((*iter).getPosition());
			for (int i = 0; i < neighbourhood.size(); i++) {
				if (neighbourhood[i]->isBombTile()) {
					bombCount++;
				}
			}
			(*iter).setBombsInNeighbourhood(bombCount);
		iter++;
	}
}

// Vygeneruje nahodne mapu, umisti na ni "totalMines" min a nastavi jednotliva policka
void Map::generateMap() {
	tiles.clear();
	for (int i = 0; i < totalMines; i++) {
		tiles.push_back(Tile{ Point{0,0} });
		tiles[i].setBombTile(true);
	}
	for (int i = 0; i < rows * columns - totalMines; i++) {
		tiles.push_back(Tile{ Point{ 0,0 } });
	}

	// zdroj random algoritmu: http://en.cppreference.com/w/cpp/algorithm/random_shuffle
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(tiles.begin(), tiles.end(), g);

	int index = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			tiles[index].setPosition(Point{ i,j });
			index++;
		}
	}
	resetBombsInNeighbourhood();
}

// Vrati okoli bunky (bunky primo sousedici s danou bunkou)
TileNeighbourhood Map::getNeighbourhood(const APoint& point) {
	TileNeighbourhood tileNeigh;
	tileNeigh.clear();
	std::vector<Tile>::iterator t_iter = tiles.begin();
	while (t_iter != tiles.end()) {
		if ((*t_iter).getPosition().isInContact(point)) {
			tileNeigh.push_back(&(*t_iter));
		}
		t_iter++;
	}
	return tileNeigh;
}

// Vrati true, pokud je na dane bunce umistena libovolna vlajka
bool Map::isAnyFlagOnPoint(const APoint& point) const {
	if (getTile(point).getTileState() == TileState::BombFlag || getTile(point).getTileState() == TileState::UnknownFlag) {
		return true;
	}
	return false;
}

// Oznaci danou bunku vlajkou "bomba"
void Map::flagPoint(const APoint& point) {
	if (getTile(point).getTileState() != TileState::Uncovered) {
		getTile(point).setTileState(TileState::BombFlag);
	}
}

// Oznaci danou bunku vlajkou "neznamo"
void Map::flagAsUnknownPoint(const APoint& point) {
	if (getTile(point).getTileState() != TileState::Uncovered) {
		getTile(point).setTileState(TileState::UnknownFlag);
	}
}

// Zrusi vlajky na dane bunce
void Map::unflagPoint(const APoint& point) {
	getTile(point).setTileState(TileState::Hidden);
}

// Odkryje bunku
// A pokud splnuje, ze nema zadne bomby v okoli, odkryvani pokracuje na vsechny
// sousedici bunky; proces se opakuje dokud odkryta bunka splnuje podminku 
// getBombsInNeighbourhood() == 0
void Map::uncoverPoint(const APoint& point) {
	getTile(point).setTileState(TileState::Uncovered);

	if (getTile(point).getBombsInNeighbourhood() == 0) {

		std::vector<ATile*> neighbourhood = getNeighbourhood(point);
		for (int i = 0; i < neighbourhood.size(); i++) {
			if(neighbourhood[i]->getTileState() == TileState::Hidden){
				uncoverPoint(neighbourhood[i]->getPosition());
			}
		}
	}
}

// Vrati pocet umistenych vlajek typu bomba
int Map::getCountOfBombFlags() const {
	return std::count_if(tiles.begin(), tiles.end(), is_bomb_flag);
}

// Vrati novy herni stav
// Pokud hrac odkryl bunku s bombou -> prohra
// Pokud zbyva odkryt bunek co je bomb -> vyhra
// Pokud hra oznacil vlajkou "bomba" vsechny bomby a zadnou bunku navic -> vyhra
// Jinak hra pokracuje normalne dal
GameState Map::getNewGameState() const {

	int countOfUncoveredTiles = std::count_if(tiles.begin(), tiles.end(), is_uncovered_tile);
	int countOfUnknownFlags = std::count_if(tiles.begin(), tiles.end(), is_unknown_flag);

	std::vector<Tile>::const_iterator c_iter = tiles.begin();
	while (c_iter != tiles.end()) {
		if ((*c_iter).getTileState() == TileState::Uncovered && (*c_iter).isBombTile()) {
			this->~Map();
			return GameState::Lose;
		}
		c_iter++;
	}

	if (countOfUncoveredTiles == (tiles.size() - totalMines) && getCountOfBombFlags() == 0 && countOfUnknownFlags == 0) {
		this->~Map();
		return GameState::Won;
		
	}

	if (countOfUncoveredTiles == (tiles.size() - totalMines) && getCountOfBombFlags() == totalMines && countOfUnknownFlags == 0) {
		this->~Map();
		return GameState::Won;
	}

	if (getCountOfBombFlags() + countOfUncoveredTiles == totalMines && countOfUnknownFlags == 0) {
		this->~Map();
		return GameState::Won;
	}

	return GameState::Playing;
}

