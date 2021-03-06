#pragma once

#include "libraries.h"

class ChessKnight {

	vector<char> step;
	pos startPos;
	int fitness;
	int stepsMade;

public:
	ChessKnight();
	ChessKnight(pos startPos);
	~ChessKnight();

	char getStep();
	vector<char> getAllSteps();
	void setAllSteps(vector<char> steps);

	pos getStartPos();

	int getFitness();
	void addFitness(int n);
	void resetFitness();
	void setStepsMade(int n);
	int getStepsMade();
};

