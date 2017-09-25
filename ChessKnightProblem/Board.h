#pragma once

#include "libraries.h"

class Board {

	vector< vector<int> > field;
	pos currentPos;
	int moveCounter;

public:
	Board();
	~Board();

	int moveKnight(char dest);
	int getMoveCounter();
	void clearField();
	void setCurrentPos(pos startPos);
	string printBoard();

private:
	int calculatePossibleMoves(pos currentPos);
};

