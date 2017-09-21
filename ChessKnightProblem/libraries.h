#pragma once

#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>

#define POPULATION_SIZE 128 //population size must be divisible by 2

using namespace std;

typedef struct {
	int x;
	int y;
}pos;