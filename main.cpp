#include "main.h"

int main(){

    //-------[EDIT THIS]-------/
    
    // Determines whether each sorting algorithm is enabled for execution.
    // true: Algorithm is enabled and will be executed.
    // false: Algorithm is disabled and will be skipped.

    bool isSortingEnabled[NUM_SORTS] = {
        false,           // Bubble Sort
        true,           // Selection Sort
        true,           // Quick Sort
        false,          // Heap Sort
        false,          // Insertion Sort
        false,          // Merge Sort
        false,          // Shell Sort
        true,          // Radix Sort
        false           // Counting Sort
    };
    //--------------------------/

    // Init
    
    SortPerformance sortPerformances[NUM_SORTS]= {
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

    bool sortPerformanceError[NUM_SORTS] = {false};
    
    cout << "[Iteration]" << endl;

    for(int iter=1;iter<=ITERATION_SIZE;iter++){
        int arr[ARRAY_SIZE] = {};
        genRandomArr(arr);
        int performanceTime;
        int* performanceCase;
        

        // Code about Progress Bar
        cout << (iter * 100 / ITERATION_SIZE) << "% ["; 
        for (int progressBar = 1; progressBar < (iter * 100 / ITERATION_SIZE) / 5 ; progressBar++){
            cout << "=";
        }
        cout << ">";
        for (int progressSpace = 0; progressSpace < 19 - ((iter * 100 / ITERATION_SIZE) / 5 + 1) ; progressSpace++){
            cout << " ";
        }
        cout << "]";
        cout << " ("  << iter << " / " << ITERATION_SIZE <<")\r" << flush;
        //------------------------

        for(int sortIdx=0;sortIdx<NUM_SORTS;sortIdx++){

            if (isSortingEnabled[sortIdx] == false){
                continue;
            } 
            performanceTime = sort(sortIdx, arr);
            if(performanceTime == -1){
                sortPerformanceError[sortIdx] = true;
                continue;
            } // case handling

            long long* performanceCase = sortPerformances[sortIdx].getPerformanceCase();
            long long tmpArr[3] = {
                    min(performanceTime, (int) performanceCase[0]), 
                    max(performanceTime, (int) performanceCase[1]), 
                    (performanceCase[2] * (iter-1) + performanceTime) / iter
            };
            sortPerformances[sortIdx].setPerformance(tmpArr, arr); 
            
        }

    }

    cout << "\nIteration completed." << endl;
     
    cout <<"\n\n======[Result]======\n" << endl;
    
    
        for(int sortIdx=0; sortIdx < NUM_SORTS; sortIdx++){
            if (isSortingEnabled[sortIdx] == false){
                continue;
            }
            long long* performanceCase = sortPerformances[sortIdx].getPerformanceCase();
            int** performanceArray = sortPerformances[sortIdx].getPerformanceArray();
            if(sortPerformanceError[sortIdx] == true){
                cout << "There were some issue(s) while performing " << sortPerformances[sortIdx].getSortName() << endl;
           
                continue;
            }
            else if(performanceCase[1]==0){
                cout << "[!] " << sortPerformances[sortIdx].getSortName() << endl;
                cout << "No Record\n" << endl;
                continue;
            } 

            cout << "[*] " << sortPerformances[sortIdx].getSortName() << endl;
            if(performanceCase[WORST] < 0) {
                cout << "[?] Warning: Time value too large, overflow may have occurred" << endl;
            }
            // print best time, array
            cout << "Best: " << performanceCase[BEST] / 1000 << " µs (" << performanceCase[BEST] << " ns)" << endl;
            
            if(PRINT_ARRAY){
                cout << "[";
                for(int arrIdx = 0; arrIdx < ARRAY_SIZE; arrIdx++) {
                    cout << performanceArray[BEST][arrIdx] << " ";
                }
                cout << "]" << endl;
            }
            // print worst time, array 
            cout << "Worst: " << performanceCase[WORST] / 1000 << " µs (" << performanceCase[WORST] << " ns)" << endl;

            if(PRINT_ARRAY){
                cout << "[";
                for(int arrIdx = 0; arrIdx < ARRAY_SIZE; arrIdx++) {
                    cout << performanceArray[WORST][arrIdx] << " ";
                }
                cout << "]" << endl;
            }


            cout << "Avg: " << performanceCase[AVERAGE] / 1000 << " µs (" << performanceCase[AVERAGE] << " ns)\n" << endl;
            
        }
    
    return 0;

}


void genRandomArr(int* arr){
    
    random_device rd;
	mt19937 mt(rd());
    
    for(int i=0;i<ARRAY_SIZE;i++){
        uniform_int_distribution<int> dist(1, MAX_NUMBER);
        arr[i] = dist(mt);
    }
}