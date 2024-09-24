#pragma once
#include <iostream>
#include <random>
#include <chrono>
#include <cstring>

#define ARRAY_SIZE 10
#define MAX_NUMBER 100

#define swap(a, b) {int tmp = a; a=b; b=tmp};

using namespace std;
using namespace std::chrono;

enum PerformanceType {
    BEST,
    WORST,
    AVERAGE
};

class SortPerformance {
private:
    char* name;
    int performanceCase[3] = {MAX_NUMBER, 0, 0}; // 0 : best, 1 : worst, 2 : average 
    int** performanceArray;  // 0 : best, 1 : worst
public:
    SortPerformance(char* _name){
        int len = strlen(_name) + 1;
        name = new char[len];
        strcpy(name, _name);
        performanceArray = new int*[2];
        for(int i=0; i<2; i++) {
            performanceArray[i] = new int[ARRAY_SIZE];
        }
    }
 
    ~SortPerformance() // 소멸자
    {
        delete[] name;

        for(int i=0;i<2;i++) {
            delete[] performanceArray[i];
        }
        delete[] performanceArray;
    }
    char* getSortName();
    int* getPerformanceCase();
    int** getPerformanceArray();
    void setPerformance(int* _performanceCase, int* _performanceArray);

};

bool testSort(int arr[ARRAY_SIZE]);
int sort(int sortIdx, int arr[ARRAY_SIZE]);

void bubbleSort(int arr[ARRAY_SIZE]);
