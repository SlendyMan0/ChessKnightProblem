#include "main.h"

int main(int argc, char* argv[]) {
	int x = 1, y = 7, popSize = 128;
	bool wasRounded = false;
	if (argc >= 2) {
		popSize = atoi(argv[1]);
		if (popSize <= 0) {
			cout << "Invalid population size.";
			system("pause > nul");
			return 1;
		}
		else if ((popSize % 2) == 1) {
			popSize++;
			wasRounded = true;
		}
	}
	if (argc >= 4) {
		x = atoi(argv[2]) - 1;
		y = atoi(argv[3]) - 1;
		if (x < 0 || x > 7) {
			cout << "Invalid board coordinates.";
			system("pause > nul");
			return 1;
		}
		else if (y < 0 || y > 7) {
			cout << "Invalid board coordinates.";
			system("pause > nul");
			return 1;
		}
	}

	cout << "Program will start with knights in the starting position of [" << x + 1 << "," << y + 1 << "].\n";
	if (wasRounded) {
		cout << "Population size must be divisible by two, and was rounded up from " << popSize - 1 << " to " << popSize << ".\n";
	}
	else {
		cout << "Population size will be: " << popSize << ".\n";
	}
	cout << "\nDo you wish to continue?\n";
	cout << "(Press ESCAPE to exit, ENTER to continue)";

	while (1) {
		if (GetAsyncKeyState(VK_ESCAPE)) return 0;
		if (GetAsyncKeyState(VK_RETURN)) break;
	}

	Generation gen(popSize, { x, y });
	int knight = 0;

	while (1) {
		knight = gen.moveGeneration();
		if (gen.getKnightFitness(knight) == 640) {
			gen.printKnight(knight);
			break;
		}
		if (GetAsyncKeyState(VK_ESCAPE)) {
			gen.printKnight(gen.currentBest());
			break;
		}
		gen.evolveGeneration();
		//system("pause > nul");
	}

	system("pause > nul");

	return 0;
}