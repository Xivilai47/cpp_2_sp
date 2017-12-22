#ifndef _DEFINES_H
#define _DEFINES_H

//  ===============================
//  === NEMENIT OBSAH SOUBORU ! ===
//  ===============================


#if (defined(_WIN32) || defined(_WIN64))
#define WINDOWS_PLATFORM
#endif

#ifdef WINDOWS_PLATFORM
#include <Windows.h>
extern HANDLE hStdin;
extern HANDLE hStdout;
#undef min
#undef max
#endif

///////////////////////////////////////////////////////////////////////////////

// Stav bunky
enum struct TileState {
	// Obsah bunky je zatim pro hrace neznamy
	Hidden,
	// Hrac umistil na bunku vlajku oznacujici bombu
	BombFlag,
	// Hrac umistil na bunku vlajku oznacujici neznamo
	UnknownFlag,
	// Odkryta bunka
	Uncovered
};

// Stav hry
enum struct GameState {
	// Probiha hra
	Playing,
	// Hrac vyhral
	Won,
	// Hrac prohral
	Lose
};

#endif