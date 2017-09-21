#pragma once

#include "libraries.h"

class Board {

	vector< vector<int> > field;
	pos currentPos;
	int moveCounter;

public:
	Board();
	~Board();

	bool moveKnight(char dest);
	int getMoveCounter();
	void clearField();
	void setCurrentPos(pos startPos);
	void printBoard();
};

