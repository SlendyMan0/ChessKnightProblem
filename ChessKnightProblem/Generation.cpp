#include "Generation.h"

int genMaxFitness = 0;
int maxFitnessKnight = 0;
int maxFitness = 0;
int winningKnight = -1;

Generation::Generation() {
}

Generation::Generation(pos start) {
	srand(time(NULL));

	vector<char> tempSteps;

	for (int i = 0; i < POPULATION_SIZE; i++) {
		ChessKnight* tempKnight = new ChessKnight(start);
		

		for (int j = 0; j < 64; j++) {
			tempSteps.push_back((rand() % 8) + 97);
		}

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
}

int Generation::moveGeneration() {
	/*
	* moving entire generation
	*/

	printf("Gen no. %7i processing. ", genNumber);

	for (int i = 0; i < POPULATION_SIZE; i++) {
		if (this->attemptFullMove(i)) {
			winningKnight = i;
			break;
		}
	}

	printf("Max fitness: %5i. Max gen fitness: %5i\n", maxFitness, genMaxFitness);

	return winningKnight;
}

bool Generation::attemptFullMove(int n) {
	
	this->board->setCurrentPos(population[n]->getStartPos());

	/*
	* we process each move separatly
	* if move was successful, we add fitness to the knight
	*/

	while (1) {
		if (this->board->moveKnight(population[n]->getStep())) {
			population[n]->addFitness();
			int x = population[n]->getFitness();
			if (x > genMaxFitness) {
				genMaxFitness = x;
				maxFitnessKnight = n;
			}

			if (x > maxFitness) {
				maxFitness = x;
			}

			if (population[n]->getFitness() == 64) {
				break;
			}
		}
		else {
			break;
		}
	}

	if (population[n]->getFitness() == 64) {
		this->board->printBoard();
		return true;//when we find answer, return true
	}
	else {
		this->board->clearField();//clearing markers for fields already steped on
		return false;//when we are still searching, return false
	}

}

void Generation::evolveGeneration() {
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
	* number of individuals mutating is determined by max fitness of the generation
	* each individual gets one of his steps mutated by randomly changing his step code
	*/
	for (int i = 0; i < genMaxFitness; i++) {
		mutatingKnightIndex = rand() % POPULATION_SIZE; //selecting knight index
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

	for (int i = 0; i < POPULATION_SIZE; i++) {
		totalFitness += this->population[i]->getFitness();
	}

	vector<int> breedingLotteryMachine;

	/*
	* next, we create vector which task is simple - become "lottery machine"
	* each individual from population gets amount of "tickets" corresponding to his fitness value
	* doing this really simplify next step, which is drawing individuals to populate new generation
	*/

	for (int i = 0; i < POPULATION_SIZE; i++) {
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

	for (int i = 0; i < POPULATION_SIZE; i++) {
		winner = breedingLotteryMachine[rand() % totalFitness];
		ChessKnight* tempKnight = new ChessKnight(population[winner]->getStartPos());
		tempKnight->setAllSteps(population[winner]->getAllSteps());
		tempPopulation.push_back(tempKnight);
	}

	for (int i = 0; i < POPULATION_SIZE; i++) {
		delete this->population[i];
	}

	this->population = tempPopulation;

	tempPopulation.clear();
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

	for (int i = 0; i < POPULATION_SIZE; i += 2) {
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
		this->population[i]->resetFitness();
		this->population[i+1]->setAllSteps(tempStepsB);
		this->population[i+1]->resetFitness();
	}
}

void Generation::printKnight(int n) {
	cout << "Knight no. " << n << " from Generation " << this->genNumber << ":\n";

	for (int i = 0; i < 64; i++) {
		cout << this->population[n]->getAllSteps()[i];
	}
	cout << "\n\n";
}