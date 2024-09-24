#pragma once
#include "sort.h"

#define ITERATION_SIZE 10
#define PIDX (sortPerformances+sortIdx*sizeof(SortPerformance))

int main();
void randomArrGen(int* arr);