#include "pch.h"
#include "utils.h"

#include <iostream>

using namespace std;

// generate random number
int gen_rand_number(int min, int max) {
	if (min < 0 || max < 0) return 0;
	return rand() % ((max - min) + 1) + min;
}