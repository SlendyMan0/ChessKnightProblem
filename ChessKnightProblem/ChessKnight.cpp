#include "ChessKnight.h"


ChessKnight::ChessKnight() {
}

ChessKnight::ChessKnight(pos startPos) {
	this->startPos = startPos;
	this->fitness = 0;
	this->stepsMade = 0;
}

ChessKnight::~ChessKnight() {
}

char ChessKnight::getStep() {
	return this->step[stepsMade];
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

void ChessKnight::addFitness(int n) {
	this->fitness+=n;
}

void ChessKnight::resetFitness() {
	this->fitness = 0;
}

void ChessKnight::setStepsMade(int n) {
	this->stepsMade = n;
}

int ChessKnight::getStepsMade() {
	return this->stepsMade;
}
