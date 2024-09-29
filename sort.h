#pragma once
#include <iostream>
#include <random>
#include <chrono>
#include <cstring>
#include <queue>
#include <algorithm>

#define LLONG_MAX 9223372036854775807

//-------[EDIT THIS]-------/
#define ARRAY_SIZE 10
#define MAX_NUMBER 100
#define ITERATION_SIZE 10

// when PRINT_ARRAY is defined as true, the {best, worst} array is printed.
// when PRINT_ARRAY is defined as false, this feature is disabled

#define PRINT_ARRAY true

//-------------------------/

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
    long long performanceCase[3] = {LLONG_MAX, 0, 0}; // 0 : best, 1 : worst, 2 : average 
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
 
    ~SortPerformance()
    {
        delete[] name;

        for(int i=0;i<2;i++) {
            delete[] performanceArray[i];
        }
        delete[] performanceArray;
    }
    char* getSortName(){
        return name;
    }
    long long* getPerformanceCase(){
        return performanceCase;
    }
    int** getPerformanceArray(){
        return performanceArray;
    }
    
    void setPerformance(long long _performanceCase[3], int _performanceArray[10]){
        
        // if new sorting case is best, then change array
        if(_performanceCase[BEST] != performanceCase[BEST]) {
            for(int i = 0; i<ARRAY_SIZE;i++){
                performanceArray[BEST][i] = _performanceArray[i];
            }
        }

        // if new sorting case is worst, then change array
        if(_performanceCase[WORST] != performanceCase[WORST]) {
            for(int i = 0; i<ARRAY_SIZE;i++){
                performanceArray[WORST][i] = _performanceArray[i];
            }
        }
        
        for(int i=0;i<3;i++){
            performanceCase[i] = _performanceCase[i];    
        }   

    }
};



int sort(int sortIdx, int arr[ARRAY_SIZE]);

// sorts
void bubbleSort(int arr[ARRAY_SIZE]);
void selectionSort(int arr[ARRAY_SIZE]);
void quickSort(int arr[ARRAY_SIZE], int low, int high);

void insertionSort(int arr[ARRAY_SIZE]);
void insertionSort(int arr[ARRAY_SIZE], int low, int high, int gap); // used for shellSort
void mergeSort(int arr[ARRAY_SIZE], int low, int high);
void shellSort(int arr[ARRAY_SIZE]);
void radixSort(int arr[ARRAY_SIZE]);

// lemma things
void swap(int& p1, int& p2);
void merge(int arr[ARRAY_SIZE], int low, int high);
int selectPivotIdx(int arr[ARRAY_SIZE], int low, int high);
bool testSort(int arr[ARRAY_SIZE]);
int getMaxDigit(int arr[ARRAY_SIZE]);