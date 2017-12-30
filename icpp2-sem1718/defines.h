#ifndef _DEFINES_H
#define _DEFINES_H

// TODO Memory leaks edit
#define _CRTDBG_MAP_ALLOC
#include<iostream>
#include <crtdbg.h>
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif
// edit end

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