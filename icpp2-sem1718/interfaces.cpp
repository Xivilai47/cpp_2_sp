#include "interfaces.h"
#include <string>
#include <iostream>

//  ===============================
//  === NEMENIT OBSAH SOUBORU ! ===
//  ===============================

using namespace std;

#ifdef WINDOWS_PLATFORM
#include <sstream>
#include <Windows.h>

#define WONLY(x) x
#else
#define WONLY(x)
#endif

APoint::APoint(int row, int column) { 
}

APoint::~APoint() {
}

ATile::ATile(const APoint& position) {
}

ATile::~ATile() {
};

AMap::AMap(int rows, int columns, int mines) : rows(rows), columns(columns), totalMines(mines) {
}

AMap::~AMap() {
}

void AMap::render() const {
	const string leftSpace = "    ";

	cout << leftSpace << " ";
	for (int j = 0; j < columns / 2; j++)
		cout << " ";
	cout << "X" << endl << endl;

	cout << leftSpace << " ";
	for (int j = 0; j < columns; j++)
		cout << getLetterForNumber(j);
	cout << " " << endl;;

	cout << leftSpace << "/";
	for (int j = 0; j < columns; j++) {
		cout << "-";
	}
	cout << "\\" << endl;

	for (int i = 0; i < rows; i++) {
		cout << (i == rows / 2 ? "Y " : "  ") << getLetterForNumber(i) << " ";

		cout << "|";

		for (int j = 0; j < columns; j++) {
			const ATile& tile = getTile(i, j);

			switch (tile.getTileState()) {
			case TileState::Hidden:
				WONLY(SetConsoleTextAttribute(hStdout, 0x11));
				cout << "#";
				break;
			case TileState::Uncovered:
				if (tile.isBombTile()) {
					WONLY(SetConsoleTextAttribute(hStdout, 0xcd));
					cout << "X";
				}
				else {
					WONLY(SetConsoleTextAttribute(hStdout, tile.getBombsInNeighbourhood() | 0x08));
					cout << (tile.getBombsInNeighbourhood() > 0 ? (char)('0' + tile.getBombsInNeighbourhood()) : ' ');
				}
				break;
			case TileState::UnknownFlag:
				WONLY(SetConsoleTextAttribute(hStdout, 0xdc));
				cout << "?";
				break;
			case TileState::BombFlag:
				WONLY(SetConsoleTextAttribute(hStdout, 0xcc));
				cout << "B";
				break;
			}

			WONLY(SetConsoleTextAttribute(hStdout, 0x07));
		}

		cout << "|";
		cout << endl;
	}

	cout << leftSpace << "\\";
	for (int j = 0; j < columns; j++) {
		cout << "-";
	}
	cout << "/" << endl;
}

char AMap::getLetterForNumber(int number) {
	if (number < 10)
		return '0' + number;

	return 'A' + (number - 10);
}

int AMap::getNumberForLetter(char letter) {
	if (letter >= '0' && letter <= '9')
		return letter - '0';

	char whichChar = letter >= 'A' && letter <= 'Z' ? 'A' : 'a';
	return 10 + (letter - whichChar);
}
