#ifndef _TESTS_H
#define _TESTS_H

//  ===============================
//  === NEMENIT OBSAH SOUBORU ! ===
//  ===============================

#include "point.h"
#include "tile.h"
#include "map.h"

#ifndef POINT_NOT_IMPLEMENTED
TEST_CASE("Point constructor and getters", "[point]") {
	Point pointAtZero{ 0, 0 };
	REQUIRE(pointAtZero.getRow() == 0);
	REQUIRE(pointAtZero.getColumn() == 0);

	Point pointSomewhere{ 10, 5 };
	REQUIRE(pointSomewhere.getRow() == 10);
	REQUIRE(pointSomewhere.getColumn() == 5);
}

TEST_CASE("Point == and != tests", "[point]") {
	Point pointAtZero{ 0, 0 };
	Point pointSomewhere{ 10, 5 };
	Point pointAtSamePlaceAsSomewhere{ 10, 5 };

	REQUIRE(pointSomewhere != pointAtZero);
	REQUIRE_FALSE(pointSomewhere == pointAtZero);

	REQUIRE(pointAtZero != pointSomewhere);
	REQUIRE_FALSE(pointAtZero == pointSomewhere);

	// ...
	REQUIRE(pointSomewhere == pointAtSamePlaceAsSomewhere);
	REQUIRE_FALSE(pointSomewhere != pointAtSamePlaceAsSomewhere);

	REQUIRE(pointAtSamePlaceAsSomewhere == pointSomewhere);
	REQUIRE_FALSE(pointAtSamePlaceAsSomewhere != pointSomewhere);
}

TEST_CASE("Point isInContact for direct contact", "[point]") {
	Point pointCenter{ 5, 5 };

	// tests direct neighbourhood
	for (int row = 4; row <= 6; row++) {
		for (int column = 4; column <= 6; column++) {
			Point testedPoint{ row, column };

			if (testedPoint == pointCenter) {
				REQUIRE_FALSE(testedPoint.isInContact(pointCenter));
				REQUIRE_FALSE(pointCenter.isInContact(testedPoint));
			}
			else {
				REQUIRE(testedPoint.isInContact(pointCenter));
				REQUIRE(pointCenter.isInContact(testedPoint));
			}
		}
	}
}

TEST_CASE("Point isInContact for far away points without contact", "[point]") {
	Point pointCenter{ 5, 5 };

	// test far away points
	Point pointNotInContact1{ 3, 3 };
	REQUIRE_FALSE(pointNotInContact1.isInContact(pointCenter));
	REQUIRE_FALSE(pointCenter.isInContact(pointNotInContact1));

	Point pointNotInContact2{ 3, 5 };
	REQUIRE_FALSE(pointNotInContact2.isInContact(pointCenter));
	REQUIRE_FALSE(pointCenter.isInContact(pointNotInContact2));
	
	Point pointNotInContact3{ 7, 7 };
	REQUIRE_FALSE(pointNotInContact3.isInContact(pointCenter));
	REQUIRE_FALSE(pointCenter.isInContact(pointNotInContact3));
	
	Point pointNotInContact4{ 0, 0 };
	REQUIRE_FALSE(pointNotInContact4.isInContact(pointCenter));
	REQUIRE_FALSE(pointCenter.isInContact(pointNotInContact4));
}
#endif

#ifndef TILE_NOT_IMPLEMENTED
TEST_CASE("Tile constructor and attributes initialization", "[tile]") {
	Tile tile{ Point{0,0} };

	REQUIRE(tile.getPosition() == (Point{ 0,0 }));
	REQUIRE(tile.getBombsInNeighbourhood() == 0);
	REQUIRE(tile.isBombTile() == false);
	REQUIRE(tile.getTileState() == TileState::Hidden);
}

TEST_CASE("Tile getters and setters", "[tile]") {
	Tile tile{ Point{ 0,0 } };

	tile.setBombsInNeighbourhood(5);
	REQUIRE(tile.getBombsInNeighbourhood() == 5);

	tile.setBombTile(true);
	REQUIRE(tile.isBombTile() == true);

	tile.setTileState(TileState::Uncovered);
	REQUIRE(tile.getTileState() == TileState::Uncovered);

	tile.setBombsInNeighbourhood(15);
	REQUIRE(tile.getBombsInNeighbourhood() == 15);

	tile.setBombTile(false);
	REQUIRE(tile.isBombTile() == false);

	tile.setTileState(TileState::BombFlag);
	REQUIRE(tile.getTileState() == TileState::BombFlag);
}
#endif

#ifndef MAP_NOT_IMPLEMENTED
TEST_CASE("Calculation of bomb count in neighbourhood with one center bomb", "[map]") {
	Map map{ 10, 10, 0 };

	Tile centerWithBomb{ Point{5,5} };
	centerWithBomb.setBombTile(true);
	map.setTile(centerWithBomb);

	map.resetBombsInNeighbourhood();

	for (int row = 4; row <= 6; row++) {
		for (int column = 4; column <= 6; column++) {
			Point testedPoint{ row, column };

			if (testedPoint != centerWithBomb.getPosition()) {
				REQUIRE(map.getTile(testedPoint).getBombsInNeighbourhood() == 1);
			}
		}
	}
}

TEST_CASE("Calculation of bomb count in neighbourhood with two center bombs", "[map]") {
	Map map{ 10, 10, 0 };

	Tile centerWithBomb1{ Point{ 5, 5 } };
	centerWithBomb1.setBombTile(true);
	map.setTile(centerWithBomb1);

	Tile centerWithBomb2{ Point{ 5, 6 } };
	centerWithBomb2.setBombTile(true);
	map.setTile(centerWithBomb2);

	map.resetBombsInNeighbourhood();

	/*
	tests for top line
	---012210---
	-----XX-----
	*/
	REQUIRE(map.getTile(Point{ 4, 3 }).getBombsInNeighbourhood() == 0);
	REQUIRE(map.getTile(Point{ 4, 4 }).getBombsInNeighbourhood() == 1);
	REQUIRE(map.getTile(Point{ 4, 5 }).getBombsInNeighbourhood() == 2);
	REQUIRE(map.getTile(Point{ 4, 6 }).getBombsInNeighbourhood() == 2);
	REQUIRE(map.getTile(Point{ 4, 7 }).getBombsInNeighbourhood() == 1);
	REQUIRE(map.getTile(Point{ 4, 8 }).getBombsInNeighbourhood() == 0);
	
	/*
	tests for bottom line
	-----XX-----
	---012210---
	*/
	REQUIRE(map.getTile(Point{ 6, 3 }).getBombsInNeighbourhood() == 0);
	REQUIRE(map.getTile(Point{ 6, 4 }).getBombsInNeighbourhood() == 1);
	REQUIRE(map.getTile(Point{ 6, 5 }).getBombsInNeighbourhood() == 2);
	REQUIRE(map.getTile(Point{ 6, 6 }).getBombsInNeighbourhood() == 2);
	REQUIRE(map.getTile(Point{ 6, 7 }).getBombsInNeighbourhood() == 1);
	REQUIRE(map.getTile(Point{ 6, 8 }).getBombsInNeighbourhood() == 0);

	/*
	tests for center line
	---01XX10---
	*/
	REQUIRE(map.getTile(Point{ 5, 3 }).getBombsInNeighbourhood() == 0);
	REQUIRE(map.getTile(Point{ 5, 4 }).getBombsInNeighbourhood() == 1);
	REQUIRE(map.getTile(Point{ 5, 7 }).getBombsInNeighbourhood() == 1);
	REQUIRE(map.getTile(Point{ 5, 8 }).getBombsInNeighbourhood() == 0);
}

TEST_CASE("Calculation of bomb count in neighbourhood with three center bombs", "[map]") {
	Map map{ 10, 10, 0 };

	Tile centerWithBomb1{ Point{ 5, 5 } };
	centerWithBomb1.setBombTile(true);
	map.setTile(centerWithBomb1);

	Tile centerWithBomb2{ Point{ 5, 6 } };
	centerWithBomb2.setBombTile(true);
	map.setTile(centerWithBomb2);

	Tile centerWithBomb3{ Point{ 4, 6 } };
	centerWithBomb3.setBombTile(true);
	map.setTile(centerWithBomb3);

	map.resetBombsInNeighbourhood();

	/*
	tests for top line
	---013X20---
	-----XX-----
	*/
	REQUIRE(map.getTile(Point{ 4, 3 }).getBombsInNeighbourhood() == 0);
	REQUIRE(map.getTile(Point{ 4, 4 }).getBombsInNeighbourhood() == 1);
	REQUIRE(map.getTile(Point{ 4, 5 }).getBombsInNeighbourhood() == 3);
	REQUIRE(map.getTile(Point{ 4, 7 }).getBombsInNeighbourhood() == 2);
	REQUIRE(map.getTile(Point{ 4, 8 }).getBombsInNeighbourhood() == 0);

	/*
	tests for center line
	------X-----
	---01XX20---
	*/
	REQUIRE(map.getTile(Point{ 5, 3 }).getBombsInNeighbourhood() == 0);
	REQUIRE(map.getTile(Point{ 5, 4 }).getBombsInNeighbourhood() == 1);
	REQUIRE(map.getTile(Point{ 5, 7 }).getBombsInNeighbourhood() == 2);
	REQUIRE(map.getTile(Point{ 5, 8 }).getBombsInNeighbourhood() == 0);
}

TEST_CASE("Tests of getNeighbourhood", "[map]") {
	Map map{ 10, 10, 0 };

	Tile centerWithBomb1{ Point{ 5, 5 } };
	centerWithBomb1.setBombTile(true);
	map.setTile(centerWithBomb1);

	// test corners
	REQUIRE(map.getNeighbourhood(Point{ 0, 0 }).size() == 3);
	REQUIRE(map.getNeighbourhood(Point{ 9, 0 }).size() == 3);
	REQUIRE(map.getNeighbourhood(Point{ 0, 9 }).size() == 3);
	REQUIRE(map.getNeighbourhood(Point{ 9, 9 }).size() == 3);

	// test sides
	REQUIRE(map.getNeighbourhood(Point{ 0, 5 }).size() == 5);
	REQUIRE(map.getNeighbourhood(Point{ 9, 5 }).size() == 5);
	REQUIRE(map.getNeighbourhood(Point{ 5, 0 }).size() == 5);
	REQUIRE(map.getNeighbourhood(Point{ 5, 9 }).size() == 5);

	// test center point
	TileNeighbourhood neighbourhood = map.getNeighbourhood(Point{ 5, 5 });

	REQUIRE(neighbourhood.size() == 8);
	for (const ATile* tile : neighbourhood) {
		REQUIRE_FALSE((tile->getPosition().getRow() == 5 && tile->getPosition().getColumn() == 5));
		REQUIRE((tile->getPosition().getRow() >= 4 && tile->getPosition().getColumn() >= 4 &&
			tile->getPosition().getRow() <= 6 && tile->getPosition().getColumn() <= 6));
	}
}

TEST_CASE("Tests of isAnyFlagOnPoint", "[map]") {
	Map map{ 10, 10, 0 };

	REQUIRE_FALSE(map.isAnyFlagOnPoint(Point{ 0, 0 }));

	Tile modifiedTileWithBombFlag{ Point{ 5, 5 } };
	modifiedTileWithBombFlag.setTileState(TileState::BombFlag);
	map.setTile(modifiedTileWithBombFlag);

	REQUIRE(map.isAnyFlagOnPoint(Point{ 5, 5 }));

	Tile modifiedTileWithUnknownFlag{ Point{ 3, 2 } };
	modifiedTileWithUnknownFlag.setTileState(TileState::UnknownFlag);
	map.setTile(modifiedTileWithUnknownFlag);

	REQUIRE(map.isAnyFlagOnPoint(Point{ 3, 2 }));
}

TEST_CASE("Tests of flagPoint", "[map]") {
	Map map{ 10, 10, 0 };

	map.flagPoint(Point{ 4, 6 });

	REQUIRE(map.getTile(Point{ 4, 6 }).getTileState() == TileState::BombFlag);
}

TEST_CASE("Tests of flagAsUnknownPoint", "[map]") {
	Map map{ 10, 10, 0 };

	map.flagAsUnknownPoint(Point{ 4, 6 });

	REQUIRE(map.getTile(Point{ 4, 6 }).getTileState() == TileState::UnknownFlag);
}

TEST_CASE("Tests of getCountOfBombFlags", "[map]") {
	Map map{ 10, 10, 0 };

	// empty map has no flags
	REQUIRE(map.getCountOfBombFlags() == 0);

	// try adding few flags
	map.flagPoint(Point{ 4, 6 });
	REQUIRE(map.getCountOfBombFlags() == 1);

	map.flagPoint(Point{ 5, 6 });
	REQUIRE(map.getCountOfBombFlags() == 2);

	map.flagPoint(Point{ 6, 6 });
	REQUIRE(map.getCountOfBombFlags() == 3);

	// unflagging should decrease count of flags
	map.unflagPoint(Point{ 4, 6 });
	REQUIRE(map.getCountOfBombFlags() == 2);

	// unknown flag should not be counted
	map.flagAsUnknownPoint(Point{ 2, 2 });
	REQUIRE(map.getCountOfBombFlags() == 2);
}

TEST_CASE("Tests of getNewGameState - playing", "[map]") {
	Map map{ 10, 10, 1 };

	// normal state is playing
	REQUIRE(map.getNewGameState() == GameState::Playing);
}

TEST_CASE("Tests of getNewGameState - lose", "[map]") {
	Map map{ 10, 10, 1 };

	// add bomb to map
	Tile tile{ Point{5, 5} };
	tile.setBombTile(true);
	map.setTile(tile);

	// normal state is playing
	REQUIRE(map.getNewGameState() == GameState::Playing);

	// trigger bomb
	map.uncoverPoint(Point{ 5, 5 });

	// player lost the game
	REQUIRE(map.getNewGameState() == GameState::Lose);
}

TEST_CASE("Tests of getNewGameState - win by flag selection", "[map]") {
	Map map{ 10, 10, 1 };

	// add bomb to map
	Tile tile{ Point{ 5, 5 } };
	tile.setBombTile(true);
	map.setTile(tile);

	// normal state is playing
	REQUIRE(map.getNewGameState() == GameState::Playing);

	// flag bomb
	map.flagPoint(Point{ 5, 5 });

	// player won
	REQUIRE(map.getNewGameState() == GameState::Won);
}

TEST_CASE("Tests of getNewGameState - win by 2 flags selection", "[map]") {
	Map map{ 10, 10, 2 };

	// add bombs to map
	Tile tile{ Point{ 5, 5 } };
	tile.setBombTile(true);
	map.setTile(tile);

	Tile tile2{ Point{ 2, 3 } };
	tile2.setBombTile(true);
	map.setTile(tile2);

	// normal state is playing
	REQUIRE(map.getNewGameState() == GameState::Playing);

	// flag bombs
	map.flagPoint(Point{ 5, 5 });
	map.flagPoint(Point{ 2, 3 });

	// player won
	REQUIRE(map.getNewGameState() == GameState::Won);
}

TEST_CASE("Tests of getNewGameState - win by uncovering all non bombs", "[map]") {
	Map map{ 3, 3, 1 };

	// add bombs to map
	Tile tile{ Point{ 0, 1 } };
	tile.setBombTile(true);
	map.setTile(tile);

	// normal state is playing
	REQUIRE(map.getNewGameState() == GameState::Playing);

	// uncover all non bomb tiles
	map.uncoverPoint(Point{ 0, 0 });
	map.uncoverPoint(Point{ 0, 2 });

	map.uncoverPoint(Point{ 1, 0 });
	map.uncoverPoint(Point{ 1, 1 });
	map.uncoverPoint(Point{ 1, 2 });

	map.uncoverPoint(Point{ 2, 0 });
	map.uncoverPoint(Point{ 2, 1 });
	map.uncoverPoint(Point{ 2, 2 });

	// player won
	REQUIRE(map.getNewGameState() == GameState::Won);
}

TEST_CASE("Tests of getNewGameState - win by uncovering all non bombs (variant 2)", "[map]") {
	Map map{ 3, 3, 2 };

	// add bombs to map
	Tile tile{ Point{ 0, 1 } };
	tile.setBombTile(true);
	map.setTile(tile);

	Tile tile2{ Point{ 2, 2 } };
	tile2.setBombTile(true);
	map.setTile(tile2);

	// normal state is playing
	REQUIRE(map.getNewGameState() == GameState::Playing);

	// uncover all non bomb tiles
	map.uncoverPoint(Point{ 0, 0 });
	map.uncoverPoint(Point{ 0, 2 });

	map.uncoverPoint(Point{ 1, 0 });
	map.uncoverPoint(Point{ 1, 1 });
	map.uncoverPoint(Point{ 1, 2 });

	map.uncoverPoint(Point{ 2, 0 });
	map.uncoverPoint(Point{ 2, 1 });

	// player won
	REQUIRE(map.getNewGameState() == GameState::Won);
}

TEST_CASE("Tests of uncoverPoint - uncovers all in empty map", "[map]") {
	Map map{ 3, 3, 1 };

	// uncovers all
	map.uncoverPoint(Point{ 0, 2 });

	REQUIRE(map.getTile(Point{ 0, 0 }).getTileState() == TileState::Uncovered);
	REQUIRE(map.getTile(Point{ 0, 1 }).getTileState() == TileState::Uncovered);
	REQUIRE(map.getTile(Point{ 0, 2 }).getTileState() == TileState::Uncovered);
	
	REQUIRE(map.getTile(Point{ 1, 0 }).getTileState() == TileState::Uncovered);
	REQUIRE(map.getTile(Point{ 1, 1 }).getTileState() == TileState::Uncovered);
	REQUIRE(map.getTile(Point{ 1, 2 }).getTileState() == TileState::Uncovered);

	REQUIRE(map.getTile(Point{ 2, 0 }).getTileState() == TileState::Uncovered);
	REQUIRE(map.getTile(Point{ 2, 1 }).getTileState() == TileState::Uncovered);
	REQUIRE(map.getTile(Point{ 2, 2 }).getTileState() == TileState::Uncovered);
}

TEST_CASE("Tests of uncoverPoint - north bomb - uncover center point", "[map]") {
	Map map{ 3, 3, 1 };

	// add bombs to map
	Tile tile{ Point{ 0, 1 } };
	tile.setBombTile(true);
	map.setTile(tile);

	map.resetBombsInNeighbourhood();

	/*
	1X1
	111
	---
	*/
	map.uncoverPoint(Point{ 1, 1 });

	REQUIRE(map.getTile(Point{ 0, 0 }).getTileState() == TileState::Hidden);
	REQUIRE(map.getTile(Point{ 0, 1 }).getTileState() == TileState::Hidden);
	REQUIRE(map.getTile(Point{ 0, 2 }).getTileState() == TileState::Hidden);

	REQUIRE(map.getTile(Point{ 1, 0 }).getTileState() == TileState::Hidden);
	REQUIRE(map.getTile(Point{ 1, 1 }).getTileState() == TileState::Uncovered);
	REQUIRE(map.getTile(Point{ 1, 2 }).getTileState() == TileState::Hidden);

	REQUIRE(map.getTile(Point{ 2, 0 }).getTileState() == TileState::Hidden);
	REQUIRE(map.getTile(Point{ 2, 1 }).getTileState() == TileState::Hidden);
	REQUIRE(map.getTile(Point{ 2, 2 }).getTileState() == TileState::Hidden);
}

TEST_CASE("Tests of uncoverPoint - north bomb - uncover south point", "[map]") {
	Map map{ 3, 3, 1 };

	// add bombs to map
	Tile tile{ Point{ 0, 1 } };
	tile.setBombTile(true);
	map.setTile(tile);

	map.resetBombsInNeighbourhood();

	/*
	1X1
	111
	---
	*/
	map.uncoverPoint(Point{ 2, 1 });

	REQUIRE(map.getTile(Point{ 0, 0 }).getTileState() == TileState::Hidden);
	REQUIRE(map.getTile(Point{ 0, 1 }).getTileState() == TileState::Hidden);
	REQUIRE(map.getTile(Point{ 0, 2 }).getTileState() == TileState::Hidden);

	REQUIRE(map.getTile(Point{ 1, 0 }).getTileState() == TileState::Uncovered);
	REQUIRE(map.getTile(Point{ 1, 1 }).getTileState() == TileState::Uncovered);
	REQUIRE(map.getTile(Point{ 1, 2 }).getTileState() == TileState::Uncovered);

	REQUIRE(map.getTile(Point{ 2, 0 }).getTileState() == TileState::Uncovered);
	REQUIRE(map.getTile(Point{ 2, 1 }).getTileState() == TileState::Uncovered);
	REQUIRE(map.getTile(Point{ 2, 2 }).getTileState() == TileState::Uncovered);
}

TEST_CASE("Tests of uncoverPoint - north bomb - uncover south-west point", "[map]") {
	Map map{ 3, 3, 1 };

	// add bombs to map
	Tile tile{ Point{ 0, 1 } };
	tile.setBombTile(true);
	map.setTile(tile);

	map.resetBombsInNeighbourhood();

	/*
	1X1
	111
	---
	*/
	map.uncoverPoint(Point{ 2, 0 });

	REQUIRE(map.getTile(Point{ 0, 0 }).getTileState() == TileState::Hidden);
	REQUIRE(map.getTile(Point{ 0, 1 }).getTileState() == TileState::Hidden);
	REQUIRE(map.getTile(Point{ 0, 2 }).getTileState() == TileState::Hidden);

	REQUIRE(map.getTile(Point{ 1, 0 }).getTileState() == TileState::Uncovered);
	REQUIRE(map.getTile(Point{ 1, 1 }).getTileState() == TileState::Uncovered);
	REQUIRE(map.getTile(Point{ 1, 2 }).getTileState() == TileState::Uncovered);

	REQUIRE(map.getTile(Point{ 2, 0 }).getTileState() == TileState::Uncovered);
	REQUIRE(map.getTile(Point{ 2, 1 }).getTileState() == TileState::Uncovered);
	REQUIRE(map.getTile(Point{ 2, 2 }).getTileState() == TileState::Uncovered);
}

TEST_CASE("Tests of uncoverPoint - north-west bomb - uncover south-west point", "[map]") {
	Map map{ 3, 3, 1 };

	// add bombs to map
	Tile tile{ Point{ 0, 0 } };
	tile.setBombTile(true);
	map.setTile(tile);

	map.resetBombsInNeighbourhood();

	/*
	X1-
	11-
	---
	*/
	map.uncoverPoint(Point{ 2, 0 });

	REQUIRE(map.getTile(Point{ 0, 0 }).getTileState() == TileState::Hidden);
	REQUIRE(map.getTile(Point{ 0, 1 }).getTileState() == TileState::Uncovered);
	REQUIRE(map.getTile(Point{ 0, 2 }).getTileState() == TileState::Uncovered);

	REQUIRE(map.getTile(Point{ 1, 0 }).getTileState() == TileState::Uncovered);
	REQUIRE(map.getTile(Point{ 1, 1 }).getTileState() == TileState::Uncovered);
	REQUIRE(map.getTile(Point{ 1, 2 }).getTileState() == TileState::Uncovered);

	REQUIRE(map.getTile(Point{ 2, 0 }).getTileState() == TileState::Uncovered);
	REQUIRE(map.getTile(Point{ 2, 1 }).getTileState() == TileState::Uncovered);
	REQUIRE(map.getTile(Point{ 2, 2 }).getTileState() == TileState::Uncovered);
}


TEST_CASE("Tests of uncoverPoint - north-west and south-east bombs - uncover south-west point", "[map]") {
	Map map{ 3, 3, 1 };

	// add bombs to map
	Tile tile{ Point{ 0, 0 } };
	tile.setBombTile(true);
	map.setTile(tile);

	Tile tile2{ Point{ 2, 2 } };
	tile2.setBombTile(true);
	map.setTile(tile2);

	map.resetBombsInNeighbourhood();

	/*
	X1-
	121
	-1X
	*/
	map.uncoverPoint(Point{ 2, 0 });

	REQUIRE(map.getTile(Point{ 0, 0 }).getTileState() == TileState::Hidden);
	REQUIRE(map.getTile(Point{ 0, 1 }).getTileState() == TileState::Hidden);
	REQUIRE(map.getTile(Point{ 0, 2 }).getTileState() == TileState::Hidden);

	REQUIRE(map.getTile(Point{ 1, 0 }).getTileState() == TileState::Uncovered);
	REQUIRE(map.getTile(Point{ 1, 1 }).getTileState() == TileState::Uncovered);
	REQUIRE(map.getTile(Point{ 1, 2 }).getTileState() == TileState::Hidden);

	REQUIRE(map.getTile(Point{ 2, 0 }).getTileState() == TileState::Uncovered);
	REQUIRE(map.getTile(Point{ 2, 1 }).getTileState() == TileState::Uncovered);
	REQUIRE(map.getTile(Point{ 2, 2 }).getTileState() == TileState::Hidden);
}

TEST_CASE("Tests of generate map", "[map]") {
	Map map{ 10, 10, 8 };

	map.generateMap();

	int foundMines = 0;
	for (int row = 0; row < 10; row++) {
		for (int column = 0; column < 10; column++) {
			if (map.getTile(Point{ row, column }).isBombTile()) {
				foundMines++;
			}
		}
	}

	REQUIRE(foundMines == 8);
}
#endif

#endif
