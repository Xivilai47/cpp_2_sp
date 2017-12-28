#include "map.h"

// ...
// zde chybi definice tridy Map
// ...

// funkcni objekty pro STL algoritmy
// fukcni objekt pro funkci getCountOfBombFlags()
bool is_bomb_flag(const ATile& tile) {
	return tile.getTileState() == TileState::BombFlag;
}

// fukcni objekty pro funkci getNewGameState()
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
	tiles.resize(rows*columns);
	//for (int i = 1; i <= rows; i++) {
	//	for (int j = 1; j <= columns; j++) {
	//		tiles.push_back(Tile{ Point{ i, j } });
	//	}
	//}
}

// Zrusi mapu
Map::~Map() {

}

// Vrati vybranou bunku
ATile& Map::getTile(const APoint& point) {
	auto iter = std::find(tiles.begin(), tiles.end(), point);
	if (iter != tiles.end()) {
		return *iter;
	}

	/*for (ATile& tile : tiles) {
		if (tile.getPosition() == point) {
			return tile;
		}
	}*/
}

// Vrati vybranou bunku
ATile& Map::getTile(int row, int column) {
	auto iter = std::find(tiles.begin(), tiles.end(), Point{ row, column });
	if (iter != tiles.end()) {
		return *iter;
	}

	//for (ATile& tile : tiles) {
	//	if (tile.getPosition().getRow() == row && tile.getPosition().getColumn == column) {
	//		return tile;
	//	}
	//}
}

// Vrati vybranou bunku
const ATile& Map::getTile(const APoint& point) const {
	auto iter = std::find(tiles.begin(), tiles.end(), point);
	if (iter != tiles.end()) {
		return *iter;
	}
	// TODO - jakej je rozdil mezi timhle a predchozim?
}

// Vrati vybranou bunku
const ATile& Map::getTile(int row, int column) const {
	auto iter = std::find(tiles.begin(), tiles.end(), Point{ row, column });
	if (iter != tiles.end()) {
		return *iter;
	}
	// TODO - jakej je rozdil mezi timhle a predchozim?
}

// Nastavi na dane bunce hodnoty dle vstupniho parametru
// Metoda je pouzita pro moznost otestovani hry
// TODO - jaka bunka je "dana bunka?"
void Map::setTile(const ATile& tile) {
	getTile(tile.getPosition()).setTileState(tile.getTileState());
}

// Prepocita vsechny hodnoty "bombsInNeighbourhood" na jednotlivych bunkach
void Map::resetBombsInNeighbourhood() {
	for (ATile& tile : tiles) {
		int bombCount = 0;
		std::vector<ATile*> neighbourhood = getNeighbourhood(tile.getPosition());
		for (int i = 0; i < 8; i++) {
			if (neighbourhood[i]->isBombTile()) {
				bombCount++;
			}
		}
		tile.setBombsInNeighbourhood(bombCount);
	}
}

// Vygeneruje nahodne mapu, umisti na ni "totalMines" min a nastavi jednotliva policka
void Map::generateMap() {
	for (int i = 0; i < totalMines; i++) {
		tiles.push_back(Tile{ Point{1,1} });
		tiles[i].setBombTile(true);
	}
	for (int i = 0; i < rows * columns - totalMines; i++) {
		tiles.push_back(Tile{ Point{1,1} });
	}
	std::random_shuffle(tiles.begin(), tiles.end());

	int index = 0;
	for (int i = 1; i <= rows; i++) {
		for (int j = 1; j <= columns; j++) {
			tiles[index].setPosition(Point{ i,j });
			index++;
		}
	}
}

// Vrati okoli bunky (bunky primo sousedici s danou bunkou)
TileNeighbourhood Map::getNeighbourhood(const APoint& point) {
	TileNeighbourhood tileNeigh;
	tileNeigh.clear();
	for (ATile& tile : tiles) {
		if (tile.getPosition().isInContact(point)) {
			tileNeigh.push_back(&tile);
		}
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
	getTile(point).setTileState(TileState::BombFlag);
}

// Oznaci danou bunku vlajkou "neznamo"
void Map::flagAsUnknownPoint(const APoint& point) {
	getTile(point).setTileState(TileState::UnknownFlag);
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
		for (ATile* tile : getNeighbourhood(point)) {
			uncoverPoint(tile->getPosition());
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

	if (std::for_each(tiles.begin(), tiles.end(), is_bomb_uncovered)) {
		return GameState::Lose;
	}

	if (countOfUncoveredTiles == totalMines && getCountOfBombFlags() == 0 && countOfUnknownFlags == 0) {
		return GameState::Won;
	}

	if (getCountOfBombFlags() == totalMines && countOfUncoveredTiles == 0 && countOfUnknownFlags == 0) {
		return GameState::Won;
	}

	if (getCountOfBombFlags() + countOfUncoveredTiles == 0 && countOfUnknownFlags == 0) {
		return GameState::Won;
	}

	return GameState::Playing;
}

