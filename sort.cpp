#include "sort.h"

void SortPerformance::setPerformance(int _performanceCase[3], int _performanceArray[10]){
    
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

char* SortPerformance::getSortName(){
    return name;
}

int* SortPerformance::getPerformanceCase(){
    return performanceCase;
}

int** SortPerformance::getPerformanceArray(){
    return performanceArray;
}

int sort(int sortIdx, int arr[ARRAY_SIZE]){

    // the array is sorted in ascending order.
    
    system_clock::time_point startTime = system_clock::now();
    switch (sortIdx) {
        case 0: {
            bubbleSort(arr);
            break;
        }

        default: {
            return -1;
        }
    }
    system_clock::time_point stopTime = system_clock::now();

    nanoseconds diffTime = duration_cast<nanoseconds>(stopTime - startTime);
    
    // test if array is sorted correctly
    if (testSort(arr) == true) {
        return (diffTime.count());
    }
    else {
        cerr << "Warning : The array is not sorted correctly." << endl;
        cout << "[";
        for(int i=0;i<ARRAY_SIZE;i++) {
            cout << arr[i] << " ";
        }
        cout << "]";
        return -1;
    }

    

}

void bubbleSort(int arr[ARRAY_SIZE]){
    int tmp;
    for(int i=0;i<ARRAY_SIZE;i++){
        for(int j=0;j<ARRAY_SIZE-i;j++){
            if(arr[j+1]<arr[j]) {
                tmp = arr[j+1];
                arr[j+1] = arr[j];
                arr[j] = tmp; // swap two elements 
            }
        }
    }
}

bool testSort(int arr[ARRAY_SIZE]){
    for(int i=0;i<ARRAY_SIZE;i++){
        if(arr[i] > arr[i+1]){
            // not sorted correctly
            return false;
        }
        
    }
    return true;
}