#pragma once
#include <iostream>
#include <random>
#include <chrono>
#include <cstring>

//-------[EDIT THIS]-------/
#define ARRAY_SIZE 60
#define MAX_NUMBER 1000000
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
    char* getSortName(){
        return name;
    }
    int* getPerformanceCase(){
        return performanceCase;
    }
    int** getPerformanceArray(){
        return performanceArray;
    }
    
    void setPerformance(int _performanceCase[3], int _performanceArray[10]){
        
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


void swap(int& p1, int& p2);
bool testSort(int arr[ARRAY_SIZE]);