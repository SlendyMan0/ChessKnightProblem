#pragma once

#include "libraries.h"
#include "ChessKnight.h"
#include "Board.h"

class Generation {

	vector<ChessKnight*> population;
	vector<ChessKnight*> prevpopulation;
	Board* board;
	int genNumber;

public:
	Generation();
	Generation(pos start);
	~Generation();

	int moveGeneration();
	void evolveGeneration();
	void printKnight(int n);
	bool attemptFullMove(int n);
	int getKnightFitness(int n);
	int currentBest();

private:
	void mutateGeneration();
	void populateGeneration();
	void crossoverGeneration();
};

