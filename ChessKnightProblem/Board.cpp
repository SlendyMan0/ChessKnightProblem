#include "Board.h"


Board::Board() {
	vector<int> temp;
	int temp2 = -1;

	for (int i = 0; i < 8; i++) {
		temp.push_back(temp2);
	}

	for (int i = 0; i < 8; i++) {
		this->field.push_back(temp);
	}

	temp.clear();

	this->moveCounter = 0;
}



Board::~Board() {
}

bool Board::moveKnight(char dest) {

	/*
	*
	*	Knight move type codes:
	*
	*	..A.B..
	*	.H...C.
	*	...S...
	*	.G...D.
	*	..F.E..
	*
	*   Where S is starting position.
	*
	*/

	pos destPos;

	switch (dest) //calculating destination of knight based on the move type
	{
	case 'a':
		destPos.x = this->currentPos.x - 1;
		destPos.y = this->currentPos.y - 2;
		break;
	case 'b':
		destPos.x = this->currentPos.x + 1;
		destPos.y = this->currentPos.y - 2;
		break;
	case 'c':
		destPos.x = this->currentPos.x + 2;
		destPos.y = this->currentPos.y - 1;
		break;
	case 'd':
		destPos.x = this->currentPos.x + 2;
		destPos.y = this->currentPos.y + 1;
		break;
	case 'e':
		destPos.x = this->currentPos.x + 1;
		destPos.y = this->currentPos.y + 2;
		break;
	case 'f':
		destPos.x = this->currentPos.x - 1;
		destPos.y = this->currentPos.y + 2;
		break;
	case 'g':
		destPos.x = this->currentPos.x - 2;
		destPos.y = this->currentPos.y + 1;
		break;
	case 'h':
		destPos.x = this->currentPos.x - 2;
		destPos.y = this->currentPos.y - 1;
		break;
	default:
		return false;
		break;
	}

	if (destPos.x < 0 || destPos.x > 7) { //move outside the playing field on x axis
		//cout << "End: Field outside board range.\n" << destPos.x << "," << destPos.y;
		//fflush(stdin);
		return false;
	}

	if (destPos.y < 0 || destPos.y > 7) { //move outside the playing field on y axis
		//cout << "End: Field outside board range.\n" << destPos.x << "," << destPos.y;;
		//fflush(stdin);
		return false;
	}

	if (this->field[destPos.x][destPos.y] == -1) { //not already steped on
		field[destPos.x][destPos.y] = ++moveCounter;

		currentPos.x = destPos.x;
		currentPos.y = destPos.y;
		

		return true;
	}
	else {
		//cout << "End: Field already stepped on.\n";
		//fflush(stdin);

		return false;
	}
}

int Board::getMoveCounter() {
	return this->moveCounter;
}

void Board::clearField() {
	this->moveCounter = 0;
	
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			this->field[i][j] = -1;
		}
	}
}

void Board::setCurrentPos(pos startPos) {
	this->field[startPos.x][startPos.y] = 0;
	this->currentPos.x = startPos.x;
	this->currentPos.y = startPos.y;
}

void Board::printBoard() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			printf("%3i ", this->field[i][j]);
		}
		cout << "\n";
	}
	cout << "\n";
}

