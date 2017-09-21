#include "main.h"

int main(int argc, char* argv[]) {
	Generation gen = Generation::Generation({ 3, 3 });
	int winningKnight = -1;

	while (winningKnight == -1) {
		winningKnight = gen.moveGeneration();
		gen.evolveGeneration();
		//system("pause > nul");
	}
	
	gen.printKnight(winningKnight);

	/*gen.moveGeneration();*/

	system("pause > nul");

	return 0;
}