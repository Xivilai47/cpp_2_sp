#include "minesweeper.h"
#include <iostream>

//  ===============================
//  === NEMENIT OBSAH SOUBORU ! ===
//  ===============================

using namespace std;

#ifdef WINDOWS_PLATFORM
//#include <sstream>
#include <Windows.h>

HANDLE hStdin;
HANDLE hStdout;

void ErrorExit(const char* c) {
	cerr << c << endl;
	exit(1);
}

void cls(HANDLE hConsole)
{
	COORD coordScreen = { 0, 0 };    // home for the cursor 
	//DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;

	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
		return;

	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	/*if (!FillConsoleOutputCharacter(hConsole,        // Handle to console screen buffer
	(TCHAR) ' ',     // Character to write to the buffer
	dwConSize,       // Number of cells to write
	coordScreen,     // Coordinates of first cell
	&cCharsWritten))// Receive number of characters written
	return;

	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
	return;

	if (!FillConsoleOutputAttribute(hConsole,         // Handle to console screen buffer
	csbi.wAttributes, // Character attributes to use
	dwConSize,        // Number of cells to set attribute
	coordScreen,      // Coordinates of first cell
	&cCharsWritten)) // Receive number of characters written
	return;
	*/
	SetConsoleCursorPosition(hConsole, coordScreen);
}
#else
#define W32ONLY(x)
#endif

void clearScreen() {
#ifdef WIN32
	cls(hStdout);
#else
	system("clear");
#endif
}

///////////////////////////////////////////////////////////////////////////////

Minesweeper::Minesweeper(int rows = 10, int columns = 10, int mines = 10) {
	this->rows = rows;
	this->columns = columns;
	this->totalMines = mines;
	this->map = new Map{ rows, columns, mines };
}

Minesweeper::~Minesweeper() {
	delete map;
}

void Minesweeper::generateMap() {
	gameState = GameState::Playing;

	map->generateMap();
}

void Minesweeper::render() const {
	map->render();
}

void Minesweeper::flipFlagOnPoint(Point point) {
	if (map->isAnyFlagOnPoint(point)) {
		map->unflagPoint(point);
	}
	else {
		map->flagPoint(point);
	}

	checkWinLose();
}

void Minesweeper::checkWinLose() {
	gameState = map->getNewGameState();
}

void Minesweeper::play() {
#ifdef WIN32
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdin == INVALID_HANDLE_VALUE)
		ErrorExit("GetStdHandle");

	//COORD c = { (short)(columns + 8 - 1), (short)(rows + 5 - 1) };
	//SetConsoleScreenBufferSize(hStdout, c);

	SMALL_RECT windowSize = { 0, 0, (short)(columns + 8), (short)(rows + 6)};
	if (!SetConsoleWindowInfo(hStdout, TRUE, &windowSize))
	{
		cout << "SetConsoleWindowInfo failed with error " << GetLastError() << endl;
	}

	CONSOLE_FONT_INFOEX cf = { 0 };
	cf.cbSize = sizeof cf;
	cf.dwFontSize.X = 12;
	cf.dwFontSize.Y = 12;
	wcscpy_s(cf.FaceName, L"Terminal");
	SetCurrentConsoleFontEx(hStdout, 0, &cf);


	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(hStdout, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(hStdout, &cursorInfo);

	DWORD fdwMode = ENABLE_EXTENDED_FLAGS;
	if (!SetConsoleMode(hStdin, fdwMode))
		ErrorExit("SetConsoleMode1");

	fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	if (!SetConsoleMode(hStdin, fdwMode))
		ErrorExit("SetConsoleMode2");

	DWORD cNumRead, i;
	INPUT_RECORD irInBuf[128];
#endif
	while (gameState == GameState::Playing) {
		clearScreen();
		render();
		cout << "Marked: " << map->getCountOfBombFlags() << " / " << totalMines << endl;

#ifdef WIN32
		bool readClick = false;
		while (!readClick) {

			if (!ReadConsoleInput(
				hStdin,      // input buffer handle 
				irInBuf,     // buffer to read into 
				128,         // size of read buffer 
				&cNumRead)) // number of records read 
				ErrorExit("ReadConsoleInput");
			// Dispatch the events to the appropriate handler. 

			for (i = 0; i < cNumRead; i++)
			{
				switch (irInBuf[i].EventType)
				{
				case KEY_EVENT: // keyboard input 
					break;

				case MOUSE_EVENT: // mouse input 
				{
					//MouseEventProc(irInBuf[i].Event.MouseEvent);
					//cout << irInBuf[i].Event.MouseEvent.dwMousePosition.X << " " << irInBuf[i].Event.MouseEvent.dwMousePosition.Y << endl;
					//cout << irInBuf[i].Event.MouseEvent.dwButtonState << endl;
					int x = irInBuf[i].Event.MouseEvent.dwMousePosition.X - 5;
					int y = irInBuf[i].Event.MouseEvent.dwMousePosition.Y - 4;
					int button = irInBuf[i].Event.MouseEvent.dwButtonState;

					/*ostringstream oss;
					oss << x << " " << y;
					SetConsoleTitleA(oss.str().c_str());*/

					if (button > 0 && irInBuf[i].Event.MouseEvent.dwEventFlags == 0) {
						if (x < 0 || y < 0 || x >= columns || y >= rows)
							break;

						if (button == FROM_LEFT_1ST_BUTTON_PRESSED)
							map->uncoverPoint(Point{ y, x });
						else if (button == RIGHTMOST_BUTTON_PRESSED)
							flipFlagOnPoint(Point{ y, x });
						else if (button == FROM_LEFT_2ND_BUTTON_PRESSED)
							map->flagAsUnknownPoint(Point{ y, x });

						readClick = true;
					}
					break;
				}

				case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing 
					break;

				case FOCUS_EVENT:  // disregard focus events 

				case MENU_EVENT:   // disregard menu events 
					break;

				default:
					ErrorExit("Unknown event type");
					break;
				}
			}
		}
#else
		char flag;
		char xChar, yChar;
		cin >> flag >> xChar >> yChar;

		int x = Map::getNumberForLetter(xChar);
		int y = Map::getNumberForLetter(yChar);

		switch (flag) {
		case 's':
		case 'S':
			map->uncoverPoint(Point{ y, x });
			break;

		case 'f':
		case 'F':
			map->flagPoint(Point{ y,x });
			break;

		case 'g':
		case 'G':
			map->unflagPoint(Point{ y,x });
			break;
		}
#endif

		checkWinLose();
	}

	clearScreen();

	for (int i = 0; i < 25; i++) {
		if (gameState == GameState::Won) {
			cout << "           You Won! :)           " << endl;
		}
		else if (gameState == GameState::Lose) {
			cout << "         BOOOOOOMMMM!            " << endl;
		}
	}
}