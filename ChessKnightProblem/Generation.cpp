#include "Generation.h"

Generation::Generation() {
}

Generation::Generation(int popSize, pos start) {
	srand(time(NULL));
	this->popSize = popSize;
	int maxFitness[2] = { 0, 0 };
	int genMaxFitness[2] = { 0, 0 };
	int maxFitnessKnight = 0;

	string fileName = "Pop";
	fileName += to_string(this->popSize);
	fileName += "_Gen0-4999.txt";
	fileGeneralResults.open(fileName, ios::trunc | ios::out);
	if (fileGeneralResults.good() != true) {
		exit(-1);
	}
	fileName = "Pop";
	fileName += to_string(this->popSize);
	fileName += "_BestKnights.txt";
	fileBestKnights.open(fileName, ios::trunc | ios::out);
	if (fileBestKnights.good() != true) {
		exit(-1);
	}

	vector<char> tempSteps;

	for (int i = 0; i < popSize; i++) {
		ChessKnight* tempKnight = new ChessKnight(start);

		for (int j = 0; j < 64; j++) {
			tempSteps.push_back((rand() % 8) + 97);
		}

		/*string test = "gfcfccabdgbbgdgdbhggfbfecfadhhgfgfadehfefaaafeaadgaghhdfabeffgga";

		for (int j = 0; j < 64; j++) {
			tempSteps.push_back(test[j]);
		}*/

		tempKnight->setAllSteps(tempSteps);
		tempSteps.clear();
		this->population.push_back(tempKnight);
	}

	this->board = new Board();
}

Generation::~Generation() {
	for (unsigned int i = 0; i < this->population.size(); i++) {
		delete this->population[i];
	}
	this->population.clear();

	delete this->board;

	fileGeneralResults.close();
	fileBestKnights.close();
}

int Generation::moveGeneration() {
	/*
	* moving entire generation
	*/

	printf("Gen no. %7i processing. ", genNumber);
	fileGeneralResults << genNumber << ";";

	for (int i = 0; i < this->popSize; i++) {
		if (this->attemptFullMove(i)) {
			maxFitnessKnight = i;
			break;
		}
	}

	printf("Max fitness: %5i. Max gen fitness: %5i\n", maxFitness[0], genMaxFitness);
	fileGeneralResults << maxFitness[0] << ";" << genMaxFitness << ";\n";

	return maxFitnessKnight;
}

bool Generation::attemptFullMove(int n) {
	
	this->board->setCurrentPos(population[n]->getStartPos());

	/*
	* we process each move separatly
	* if move was successful, we add fitness to the knight
	*/

	int fitnessToAdd = 0;
	int x = 0;
	while (1) {
		fitnessToAdd = this->board->moveKnight(population[n]->getStep());
		if (fitnessToAdd == -1) {
			population[n]->addFitness(10);
		}
		else {
			population[n]->addFitness(fitnessToAdd);
		}
		population[n]->setStepsMade(this->board->getMoveCounter());
		x = population[n]->getFitness();

		if (x > genMaxFitness) {
			genMaxFitness = x;
			maxFitnessKnight = n;
		}

		if (x > maxFitness[0]) {
			maxFitness[0] = x;
			bestSteps = this->population[n]->getAllSteps();
		}

		if (population[n]->getFitness() == 640) {
			break;
		}

		if (fitnessToAdd != -1) {
			break;		
		}

	}

	if (population[n]->getFitness() == 640) {
		return true;//when we find answer, return true
	}
	else {	
		this->board->clearField();//clearing markers for fields already steped on
		return false;//when we are still searching, return false
	}
}

void Generation::evolveGeneration() {
	if (this->genNumber == 0) this->maxFitness[1] = this->maxFitness[0];//saving first fitness milestone

	/*
	* to keep up the progress, we periodically check the population for progress
	* every 5000 generations, we compare max fitness from 5000 generations ago with current one
	* if nothing changed, we compare individuals
	* 
	* additionally, we use this check to save best knights at the time of those generations to file
	* also, we open new file to save generations fitness data
	*/

	if ((this->genNumber % 5000) == 4999) {//checking after each 5000 generations
		fileGeneralResults.close();

		string fileName = "Pop";
		fileName += to_string(this->popSize);
		fileName += "_Gen";
		fileName += to_string(this->genNumber + 1);
		fileName += "-";
		fileName += to_string(this->genNumber + 5000);
		fileName += ".txt";
		fileGeneralResults.open(fileName, ios::trunc | ios::out);//opening new file for general data
		if (fileGeneralResults.good() != true) {
			exit(-1);
		}

		printKnight(this->maxFitnessKnight, false);//saving current best knight

		this->prevpopulation = this->population;//saving population

		if (maxFitness[0] == maxFitness[1]) {//checking if progress was made
			if (compareKnights()) {//comparing individual knights
				refreshPopulation();
			}
		}

		maxFitness[1] = maxFitness[0];
	}

	this->populateGeneration();
	this->mutateGeneration();
	this->crossoverGeneration();
	this->genNumber++;
	genMaxFitness = 0;
	
}

void Generation::mutateGeneration() {
	int mutatingKnightIndex, mutatingStepIndex, mutationValue;
	vector<char> tempSteps;

	/*
	* mutating random individuals
	* 
	* number of individuals mutating is determined by max fitness of the generation, 
	* divided by 10 multiplyed by size of population divided by 25
	* this makes sure that bigger populations have more mutations and
	* more moves algorythm was able to make, more mutations occurs
	* that way, algorythm doesn't block itself with stale population quite so quickly
	*
	* each individual gets one of his steps mutated by randomly changing his step code
	*/
	int mutationChance = (int)(popSize / 100);//value used to determine amount of mutations, bigger for bigger populations
	if (mutationChance == 0) mutationChance = 1;//making sure that there is always at least one mutation
	for (int i = 0; i < (int)((genMaxFitness / 40) * mutationChance); i++) {
		mutatingKnightIndex = rand() % this->popSize; //selecting knight index
		mutatingStepIndex = rand() % 64;//selecting step index
		mutationValue = rand() % 8;//this number will determine by how much will we shift step code from a to g and wrapping around
		
		tempSteps = this->population[mutatingKnightIndex]->getAllSteps();
		tempSteps[mutatingStepIndex] = ((tempSteps[mutatingStepIndex] - 97 + mutationValue) % 8) + 97;
		this->population[mutatingKnightIndex]->setAllSteps(tempSteps);
	}

	tempSteps.clear();
}

void Generation::populateGeneration() {
	int totalFitness = 0;

	/*
	* first step is to get sum of all fitnesses
	*/

	for (int i = 0; i < this->popSize; i++) {
		totalFitness += this->population[i]->getFitness();
	}

	vector<int> breedingLotteryMachine;

	/*
	* next, we create vector which task is simple - become "lottery machine"
	* each individual from population gets amount of "tickets" corresponding to his fitness value
	* doing this really simplify next step, which is drawing individuals to populate new generation
	*/

	for (int i = 0; i < this->popSize; i++) {
		for (int j = 0; j < this->population[i]->getFitness(); j++)
		{
			breedingLotteryMachine.push_back(i);
		}
	}

	vector<ChessKnight*> tempPopulation;
	int winner;

	/*
	* here, we select amount of individuals described by POPULATION_SIZE
	* the same individual can be selected multiple times, to "spread his genes"
	* we replace the population with individuals selected from this step
	* after this step, population is randomized and ready for crossing-over
	*/

	for (int i = 0; i < this->popSize; i++) {
		winner = breedingLotteryMachine[rand() % totalFitness];
		ChessKnight* tempKnight = new ChessKnight(population[winner]->getStartPos());
		tempKnight->setAllSteps(population[winner]->getAllSteps());
		tempPopulation.push_back(tempKnight);
	}

	for (int i = 0; i < this->popSize; i++) {
		delete this->population[i];
	}

	this->population = tempPopulation;

	tempPopulation.clear();
	breedingLotteryMachine.clear();
}

void Generation::crossoverGeneration() {
	vector<char> tempStepsA, tempStepsB, partA, partB;
	int cutIndex;

	/*
	* creating new population using crossing-over
	* we take two individuals from our already randomized population
	* point in which genetic code of both individuals is cut is randomized for each pair
	* after this, the new generation is ready for some action :)
	*/

	for (int i = 0; i < this->popSize; i += 2) {
		tempStepsA = this->population[i]->getAllSteps();
		tempStepsB = this->population[i+1]->getAllSteps();

		cutIndex = (rand() % 62) + 1;//randomizing cut point

		/*
		* vectors partA and part B are used to extract a parts of original genetic codes
		* we copy original vectors, and erase indexes from 0 to cut point
		*/

		partA = tempStepsA;
		partB = tempStepsB;
		partA.erase(partA.begin(), partA.begin() + cutIndex);
		partB.erase(partB.begin(), partB.begin() + cutIndex);

		/*
		* this function allows us to easily replace parts of vectors by overriding existing data in vectors
		* with our cut out part after the cut point
		*/

		copy_n(partA.begin(), partA.size(), tempStepsB.begin() + cutIndex);
		copy_n(partB.begin(), partB.size(), tempStepsA.begin() + cutIndex);

		this->population[i]->setAllSteps(tempStepsA);
		//this->population[i]->resetFitness();
		//this->population[i]->setStepsMade(0);
		this->population[i+1]->setAllSteps(tempStepsB);
		//this->population[i+1]->resetFitness();
		//this->population[i+1]->setStepsMade(0);
	}
}

void Generation::printKnight(int n, bool toConsole) {
	int tempGenNumber;
	vector<char> tempSteps;
	int tempStepsMade;
	bool currentPop = true;
	int tempFitness;

	this->board->clearField();
	if (population[n]->getFitness() == genMaxFitness) {
		tempGenNumber = this->genNumber;
		tempSteps = this->population[n]->getAllSteps();
		tempStepsMade = this->population[n]->getStepsMade();
		this->board->setCurrentPos(population[n]->getStartPos());
		tempFitness = population[n]->getFitness();
		population[n]->setStepsMade(0);
	}
	else {
		tempGenNumber = this->genNumber - 1;
		tempSteps = this->prevpopulation[n]->getAllSteps();
		tempStepsMade = this->prevpopulation[n]->getStepsMade();
		this->board->setCurrentPos(prevpopulation[n]->getStartPos());
		tempFitness = prevpopulation[n]->getFitness();
		prevpopulation[n]->setStepsMade(0);
		currentPop = false;
	}

	if (toConsole) {
		cout << "\nKnight no. " << n << " from Generation " << tempGenNumber << " with fitness of " << tempFitness << ":\n\n";
		for (int i = 0; i < 64; i++) {
			cout << tempSteps[i];
		}
		cout << "\n\nMade: " << tempStepsMade << " moves.\n\n";
	}
	fileBestKnights << "\nKnight no. " << n << " from Generation " << tempGenNumber << " with fitness of " << tempFitness << ":\n\n";
	for (int i = 0; i < 64; i++) {
		fileBestKnights << tempSteps[i];
	}
	fileBestKnights << "\n\nMade: " << tempStepsMade << " moves.\n\n";

	int test;
	while (1) {
		if (currentPop) {
			test = this->board->moveKnight(population[n]->getStep());
			population[n]->setStepsMade(this->board->getMoveCounter());

			if (population[n]->getStepsMade() >= 64) break;
			if (test != -1) break;
		}
		else {
			test = this->board->moveKnight(prevpopulation[n]->getStep());
			prevpopulation[n]->setStepsMade(this->board->getMoveCounter());

			if (prevpopulation[n]->getStepsMade() >= 64) break;
			if (test != -1) break;
		}
	}
	if (toConsole) {
		cout << board->printBoard();
	}
	fileBestKnights << board->printBoard();
	fileBestKnights << "\n------------------------------------------------------";
	if (toConsole && (this->maxFitness[0] != 640)) {
		this->population[n]->setStepsMade(0);
		this->population[n]->setAllSteps(bestSteps);
		this->board->clearField();
		this->board->setCurrentPos(this->population[n]->getStartPos());
		while (1) {
			test = this->board->moveKnight(population[n]->getStep());
			population[n]->setStepsMade(this->board->getMoveCounter());

			if (population[n]->getStepsMade() >= 64) break;
			if (test != -1) break;
		}

		cout << "\nBest generated path with "<< this->population[n]->getStepsMade() <<" moves:\n\n";
		for (int i = 0; i < 64; i++) {
			cout << this->population[n]->getAllSteps()[i];
		}
		cout << "\n\n";
		cout << board->printBoard();

		fileBestKnights << "\nBest generated path with " << this->population[n]->getStepsMade() << " moves:\n\n";
		for (int i = 0; i < 64; i++) {
			fileBestKnights << this->population[n]->getAllSteps()[i];
		}
		fileBestKnights << "\n\n";
		fileBestKnights << board->printBoard();
	}
}

int Generation::getKnightFitness(int n) {
	return this->population[n]->getFitness();
}

int Generation::currentBest() {
	return maxFitnessKnight;
}

bool Generation::compareKnights() {
	int similarCount = 0;
	int tempCount = 0;

	for (unsigned int i = 0; i < this->population.size(); i++) {
		tempCount = 0;
		for (unsigned int j = 0; j < this->population.size(); j++) {
			if ((this->population[i]->getAllSteps() == this->population[j]->getAllSteps()) && (i != j)) tempCount++;
		}
		if (tempCount > similarCount) similarCount = tempCount;
	}

	fileBestKnights << "\n"<< similarCount << " knights were the same\n";
	fileBestKnights << "------------------------------------------------------";

	if (similarCount > this->popSize / 2) return true;
	else return false;
}

void Generation::refreshPopulation() {
	pos startPos = this->population[0]->getStartPos();
	vector<char> tempSteps;

	for (unsigned int i = 0; i < this->population.size(); i += 2) {
		ChessKnight* tempKnight = new ChessKnight(startPos);

		for (int j = 0; j < 64; j++) {
			tempSteps.push_back((rand() % 8) + 97);
		}

		tempKnight->setAllSteps(tempSteps);
		tempSteps.clear();

		this->population[i] = tempKnight;
	}
}