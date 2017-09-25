#include "Board.h"


Board::Board() {
	vector<int> temp;

	for (int i = 0; i < 8; i++) {
		temp.push_back(-1);
	}

	for (int i = 0; i < 8; i++) {
		this->field.push_back(temp);
	}

	temp.clear();

	this->moveCounter = 0;
}

Board::~Board() {
}

int Board::moveKnight(char dest) {

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
	pos tempPos;

	tempPos.x = this->currentPos.x;
	tempPos.y = this->currentPos.y;

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
		return 0;
		break;
	}

	if (destPos.x < 0 || destPos.x > 7) { //move outside the playing field on x axis
		return calculatePossibleMoves(tempPos);
	}
	else if (destPos.y < 0 || destPos.y > 7) { //move outside the playing field on y axis
		return calculatePossibleMoves(tempPos);
	}
	else if (this->field[destPos.x][destPos.y] != -1) { //already steped on
		return calculatePossibleMoves(tempPos);
	}
	else {
		field[destPos.x][destPos.y] = ++moveCounter;

		currentPos.x = destPos.x;
		currentPos.y = destPos.y;

		return -1;
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

string Board::printBoard() {
	string printedBoard;

	printedBoard += "   [ 1][ 2][ 3][ 4][ 5][ 6][ 7][ 8]\n";
	for (int i = 0; i < 8; i++) {
		printedBoard += "[";
		printedBoard += to_string(i + 1);
		printedBoard += "]";
		for (int j = 0; j < 8; j++) {
			if (this->field[i][j] != -1) {
				if (this->field[i][j] < 10) {
					printedBoard += "  ";
					printedBoard += to_string(this->field[i][j]);
					printedBoard += " ";
				}
				else {
					printedBoard += " ";
					printedBoard += to_string(this->field[i][j]);
					printedBoard += " ";
				}
			}
			else
			{
				printedBoard += "  x ";
			}
		}
		printedBoard += "\n";
	}
	printedBoard += "\n";

	return printedBoard;
}

int Board::calculatePossibleMoves(pos currentPos) {
	vector<pos> destPosVec;
	pos destPos;
	int possibleMoves = 8;

	destPos.x = currentPos.x - 1;
	destPos.y = currentPos.y - 2;
	destPosVec.push_back(destPos);

	destPos.x = currentPos.x + 1;
	destPos.y = currentPos.y - 2;
	destPosVec.push_back(destPos);

	destPos.x = currentPos.x + 2;
	destPos.y = currentPos.y - 1;
	destPosVec.push_back(destPos);

	destPos.x = currentPos.x + 2;
	destPos.y = currentPos.y + 1;
	destPosVec.push_back(destPos);

	destPos.x = currentPos.x + 1;
	destPos.y = currentPos.y + 2;
	destPosVec.push_back(destPos);

	destPos.x = currentPos.x - 1;
	destPos.y = currentPos.y + 2;
	destPosVec.push_back(destPos);

	destPos.x = currentPos.x - 2;
	destPos.y = currentPos.y + 1;
	destPosVec.push_back(destPos);

	destPos.x = currentPos.x - 2;
	destPos.y = currentPos.y - 1;
	destPosVec.push_back(destPos);

	for (unsigned int i = 0; i < destPosVec.size(); i++) {
		if (destPosVec[i].x < 0 || destPosVec[i].x > 7) { //move outside the playing field on x axis
			possibleMoves--;
		}
		else if (destPosVec[i].y < 0 || destPosVec[i].y > 7) { //move outside the playing field on y axis
			possibleMoves--;
		}
		else if (this->field[destPosVec[i].x][destPosVec[i].y] != -1) {
			possibleMoves--;
		}
	}

	destPosVec.clear();

	return (int)((64 - moveCounter)*possibleMoves/8);
}