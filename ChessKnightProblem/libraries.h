#pragma once

#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <windows.h>

#define POPULATION_SIZE 128 //population size must be divisible by 2
#define MUTATION_CHANCE 4 //temp : (int)(genMaxFitness/20)

using namespace std;

typedef struct {
	int x;
	int y;
}pos;