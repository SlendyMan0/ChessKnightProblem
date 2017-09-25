#pragma once

#include "libraries.h"
#include "ChessKnight.h"
#include "Board.h"

class Generation {

	vector<ChessKnight*> population;
	vector<ChessKnight*> prevpopulation;
	vector<char> bestSteps;
	Board* board;
	int genNumber;
	fstream fileGeneralResults;
	fstream fileBestKnights;
	int popSize;
	int maxFitness[2];
	int genMaxFitness;
	int maxFitnessKnight;

public:
	Generation();
	Generation(int popSize, pos start);
	~Generation();

	int moveGeneration();
	void evolveGeneration();
	void printKnight(int n, bool toConsole = true);
	int getKnightFitness(int n);
	int currentBest();

private:
	bool attemptFullMove(int n);
	void mutateGeneration();
	void populateGeneration();
	void crossoverGeneration();
	bool compareKnights();
	void refreshPopulation();
};

