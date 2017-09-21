#include "ChessKnight.h"


ChessKnight::ChessKnight() {
}

ChessKnight::ChessKnight(pos startPos) {
	this->startPos = startPos;
	this->fitness = 0;
}

ChessKnight::~ChessKnight() {
}

char ChessKnight::getStep() {
	return this->step[fitness];//we use fitness as our iterator
}

vector<char> ChessKnight::getAllSteps() {
	return this->step;
}

void ChessKnight::setAllSteps(vector<char> steps) {
	this->step = steps;
}

pos ChessKnight::getStartPos() {
	return this->startPos;
}

int ChessKnight::getFitness() {
	return this->fitness;
}

void ChessKnight::addFitness() {
	this->fitness++;
}

void ChessKnight::resetFitness() {
	this->fitness = 0;
}
