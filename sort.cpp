#include "sort.h"

int sort(int sortIdx, int arr[ARRAY_SIZE]){

    // the array is sorted in ascending order.
    
    system_clock::time_point startTime = system_clock::now();
    switch (sortIdx) {
        case 0: {
            bubbleSort(arr);
            break;
        } 
        case 1: {
            selectionSort(arr);
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
                swap(arr[j], arr[j+1]); 
            }
        }
    }
}

void selectionSort(int arr[ARRAY_SIZE]){
    int min;
    for(int i=0;i<ARRAY_SIZE-1;i++){
        min = i;
        for(int j=i;j<ARRAY_SIZE;j++){
            if(arr[min] > arr[j]) {
                min = j;
            }
        }
        if(min != i) {
            swap(arr[min], arr[i]);
        }
    }
}


void swap(int& p1, int& p2) {
    int tmp = p1;
    p1 = p2;
    p2 = tmp;
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