// odkomentujte pokud chcete spustit sadu testu 
//#define TESTS

// TODO Memory leaks edit
#define _CRTDBG_MAP_ALLOC
#include<iostream>
#include <crtdbg.h>
// edit end

// nastaveni hry:
// odkomentujte pokud chcete pokazde jinou hru
#define ALLOW_MAP_RANDOMIZE
// parametry
#define MINESWEEPER_ROWS    20
#define MINESWEEPER_COLUMNS 20
#define MINESWEEPER_MINES   40

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
	{
#ifdef ALLOW_MAP_RANDOMIZE
	std::srand((unsigned int)std::time(NULL));
#endif
	
	Minesweeper mines{MINESWEEPER_ROWS, MINESWEEPER_COLUMNS, MINESWEEPER_MINES};

	mines.generateMap();
	mines.play();
	}

	// TODO Memory leaks detection
	// pridany chlupate zavorky kolem kodu v main() aby byl zavolan destruktor Minesweeper mines jeste pred memory dumpem
	// statistics - https://msdn.microsoft.com/en-us/library/x98tx3cf.aspx
	_CrtMemState s1;
	_CrtMemCheckpoint(&s1);
	_CrtMemDumpStatistics(&s1);
	_CrtDumpMemoryLeaks();
	// edit end

	return 0;
}

#endif
