#include "main.h"

int main(int argc, char* argv[]) {
	Generation gen = Generation::Generation({ 3, 3 });
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