#ifndef _MINESWEEPER_H
#define _MINESWEEEPER_H

//  ===============================
//  === NEMENIT OBSAH SOUBORU ! ===
//  ===============================

#include "defines.h"
#include "map.h"

struct Minesweeper {

private:
	GameState gameState;
	int rows;
	int columns;
	int totalMines;
	AMap* map;

public:
	Minesweeper(int rows, int columns, int mines);
	~Minesweeper();

	void generateMap();
	void render() const;

	void flipFlagOnPoint(Point point);
	void checkWinLose();
	void play();

};

#endif