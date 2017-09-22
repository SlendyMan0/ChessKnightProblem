#include "main.h"

int main(int argc, char* argv[]) {
	int x = 3, y = 3;
	if (argc >= 3) {
		x = atoi(argv[1]) - 1;
		y = atoi(argv[2]) - 1;
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

	Generation gen({ x, y });
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