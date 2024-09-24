#include "main.h"

int main(){
    
    // Init
    SortPerformance sortPerformances[9]= {
        SortPerformance((char *) "Bubble Sort"),
        SortPerformance((char *) "Selection Sort"),
        SortPerformance((char *) "Quick Sort"),
        SortPerformance((char *) "Heap Sort"),
        SortPerformance((char *) "Insertion Sort"),
        SortPerformance((char *) "Merge Sort"),
        SortPerformance((char *) "Shell Sort"),
        SortPerformance((char *) "Radix Sort"),
        SortPerformance((char *) "Counting Sort")
    };
    
    
    for(int iter=1;iter<ITERATION_SIZE;iter++){
        int arr[ARRAY_SIZE] = {};
        randomArrGen(arr);
        
        int performanceTime;
        int* performanceCase;

        cout << "Iteration "  << iter << endl;
        
        for(int sortIdx=0;sortIdx<9;sortIdx++){
            performanceTime = sort(sortIdx, arr);
            if(performanceTime == -1){
                cout << "There were some issue(s) while performing " << sortPerformances[sortIdx].getSortName() << endl;
                continue;
            } // case handling
            int* performanceCase = sortPerformances[sortIdx].getPerformanceCase();
            int tmpArr[3] = {
                    min(performanceTime, performanceCase[0]), 
                    max(performanceTime, performanceCase[1]), 
                    (performanceCase[2] * (iter-1) + performanceTime) / iter
            };
            cout << tmpArr[0] << " " << tmpArr[1] << " " << tmpArr[2];
            sortPerformances[sortIdx].setPerformance(tmpArr, arr); 
            
        }

    }

    cout << "Iteration completed." << endl;

    cout <<"======[Result]======" << endl;
    for(int sortIdx=0;sortIdx<1;sortIdx++){
        int* performanceCase = sortPerformances[sortIdx].getPerformanceCase();
        int** performanceArray = sortPerformances[sortIdx].getPerformanceArray();
        if(performanceCase[1]==0){
            cout << "[!] No Record" << endl;
            continue;
        }

        cout << "[*]" << sortPerformances[sortIdx].getSortName() << endl;
        // print best time, array
        cout << "Best: " << performanceCase[BEST] << " ns" << endl;
        cout << "[";
        for(int arrIdx = 0; arrIdx < ARRAY_SIZE; arrIdx++) {
            cout << performanceArray[BEST][arrIdx] << " ";
        }
        cout << "]" << endl;
         
        // print worst time, array 
        cout << "Worst: " << performanceCase[WORST] << " ns" << endl;
        cout << "[";
        for(int arrIdx = 0; arrIdx < ARRAY_SIZE; arrIdx++) {
            cout << performanceArray[WORST][arrIdx] << " ";
        }
        cout << "]" << endl;
         

        cout << "Avg: " << performanceCase[AVERAGE] << " ns" << endl;
         
    }

    return 0;

}


void randomArrGen(int* arr){
    
    random_device rd;
	mt19937 mt(rd());
    
    for(int i=0;i<ARRAY_SIZE;i++){
        uniform_int_distribution<int> dist(1, MAX_NUMBER);
        arr[i] = dist(mt);
    }
}
