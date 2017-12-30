// odkomentujte pokud chcete spustit sadu testu 
//#define TESTS

// nastaveni hry:
// odkomentujte pokud chcete pokazde jinou hru
//#define ALLOW_MAP_RANDOMIZE
// parametry
#define MINESWEEPER_ROWS    100
#define MINESWEEPER_COLUMNS 100
#define MINESWEEPER_MINES   500

//  ===============================
//  === NEMENIT OBSAH SOUBORU ! ===
//  ===============================

#include "minesweeper.h"
#include <cstdlib>
#include <ctime>

#ifdef TESTS
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "tests.h"
#else

int main() {
#ifdef ALLOW_MAP_RANDOMIZE
	std::srand((unsigned int)std::time(NULL));
#endif
	
	Minesweeper mines{MINESWEEPER_ROWS, MINESWEEPER_COLUMNS, MINESWEEPER_MINES};

	mines.generateMap();
	mines.play();

	// TODO uprava start
	system("pause");
	// TODO uprava konec
	return 0;
}

#endif
