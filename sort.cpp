#include "sort.h"
#include <random>
#include <time.h>

static random_device rd;

int sort(int sortIdx, int arr[ARRAY_SIZE]){

    int arrTmp[ARRAY_SIZE];
    copy_n(arr, ARRAY_SIZE, arrTmp);

    // the array is sorted in ascending order.
    system_clock::time_point startTime = system_clock::now();
    switch (sortIdx) {
        case 0: {
            bubbleSort(arrTmp);
            break;
        } 
        case 1: {
            selectionSort(arrTmp);
            break;
        }
        case 2: {
            quickSort(arrTmp, 0, ARRAY_SIZE-1);
            break;
        }
        case 3: { // heapSort
            return -1; // 🚧🚧
        }
        case 4: {
            insertionSort(arrTmp);
            break;
        }
        case 5: {
            mergeSort(arrTmp, 0, ARRAY_SIZE-1);
            break;
        }
        case 6: {
            shellSort(arrTmp);
            break;
        }
        case 7: {
            radixSort(arrTmp);
            break;
        }
        case 8: {// Counting Sort
            return -1;
        }
        case 9: {
            bogoSort(arrTmp);
            break;
        }
        case 10: {
            // bogobogoSort
            return -1;
        }

        default: {
            return -1;
        }
    }
    
    system_clock::time_point stopTime = system_clock::now();

    nanoseconds diffTime = duration_cast<nanoseconds>(stopTime - startTime);
    
    // test if array is sorted correctly
    if (testSort(arrTmp) == true) {
        return (diffTime.count());
    }
    else {
        cerr << "\nWarning : The array is not sorted correctly. " << endl;
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

void quickSort(int arr[ARRAY_SIZE], int low, int high){
    // this quickSort uses the three-of-median method

    if (low < high){
        threeOfMidian(arr, low, high);

        if(high-low >= 3){
            int pivot = arr[high-1];
            int left = low;
            int right = high-1;

            while(left < right)
            {
                while (arr[++left] < pivot && left<high );
                while (arr[--right] > pivot && low<right);
                
                if(left >= right) break;
                swap(arr[left], arr[right]);   
            }

                swap(arr[high-1], arr[left]); // swap pivot to right
                quickSort(arr, low, left-1);
                quickSort(arr, left+1, high);
            
        }
        
    }
    
}

void insertionSort(int arr[ARRAY_SIZE]){
    int i, j, key;
    for(i=1;i<ARRAY_SIZE;i++) {
        key = arr[i];

        for(j=i-1; j>=0 && arr[j] > key; j--){
            arr[j+1] = arr[j];
        }
        arr[j+1] = key;
    }   
}

// this insertionSort is used for shellSort
void insertionSort(int arr[ARRAY_SIZE], int low, int high, int gap){
    int i, j, key;
    for(i = low ; i <= high ; i += gap) {
        key = arr[i];

        for(j = i - gap; j >= low && arr[j] > key; j -= gap){
            arr[j+gap] = arr[j];
        }
        arr[j+gap] = key;
    }   
}

void mergeSort(int arr[ARRAY_SIZE], int low, int high){
    // Recursively divide the arr until each sublist contains only one element
    if(low<high){ 
        int mid = (low + high) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid+1, high);

        // Merge the divided sublists
        merge(arr, low, high);
    }
}

void shellSort(int arr[ARRAY_SIZE]){
    int i, gap;
    for(gap = ARRAY_SIZE / 2; gap > 0 ; gap /= 2) {
        if(gap % 2 == 0){
            gap++;
        } 
        for (i = 0; i < gap; i++){
            insertionSort(arr, i, ARRAY_SIZE-1, gap);
        }
    }
}

void radixSort(int arr[ARRAY_SIZE]){
    queue<int> q[10];
    int maxDigit = getMaxDigit(arr);
    for(int digit = 1; digit <= maxDigit; digit++){
        for(int arrIdx = 0; arrIdx <ARRAY_SIZE; arrIdx++){
            q[arr[arrIdx] / (int) pow(10, digit-1) % 10 ].push(arr[arrIdx]);
        }
        int arrIdx = 0;
        for(int qIdx = 0; qIdx <10; qIdx++){
            while(!q[qIdx].empty()){
                arr[arrIdx] = q[qIdx].front(); 
                q[qIdx].pop();
                arrIdx++;
            }
        }
    }
}

void bogoSort(int arr[ARRAY_SIZE]){
    while (!testSort(arr, false)){
        shuffleArray(arr);
    }
}

void bogobogoSort(int arr[ARRAY_SIZE]){
    // TODO: bogobogo sort
}

//-----------

void threeOfMidian(int arr[ARRAY_SIZE], int low, int high) {
    
    // used for quick sort
    // sort three values which idx is {low, mid, high}
    // save pivot value to arr[high-1]

    int mid = (low + high) / 2;
    if(arr[low]>arr[mid]) swap(arr[low], arr[mid]);
	if(arr[mid]>arr[high]) swap(arr[mid], arr[high]);
	if(arr[low]>arr[mid]) swap(arr[low], arr[mid]);

    swap(arr[mid], arr[high-1]);
    
}

void merge(int arr[ARRAY_SIZE], int low, int high){
    // sorted[] is a temporary sublist used to merge two divided sublists. 
    // After storing in sorted[] through the following process, the contents of sorted[] are then saved in arr[].
    int* sorted = new int[high - low + 1];
    int i, j, k;
    int mid = (high + low) / 2;
    i = low; // left arr idx
    j = mid + 1; // right arr idx
    k = 0; // sorted arr idx

    while (i <= mid && j <= high){
        if(arr[i] <= arr[j]) {
            sorted[k++] = arr[i++];
        }
        else {   
            sorted[k++] = arr[j++];
        }
    }

    if (i > mid)
        while(j<=high) sorted[k++] = arr[j++];
    else
        while(i<=mid) sorted[k++] = arr[i++];
        

    for(i = low, k=0 ; i <= high ; i++, k++) {
        arr[i] = sorted[k];
    }

    delete[] sorted;
}

void swap(int& p1, int& p2) {
    int tmp = p1;
    p1 = p2;
    p2 = tmp;
}

bool testSort(int arr[ARRAY_SIZE], bool debug){
    for(int i=0;i<ARRAY_SIZE-1;i++){
        if(arr[i] > arr[i+1]){
            // not sorted correctly
            if (debug) cout << "[?] { idx " << i << ": " << arr[i] << ", idx " << i+1 << ": " << arr[i+1] << " }\n"<< endl;
            return false;
        }
    }
    return true;
}

int getMaxDigit(int arr[ARRAY_SIZE]){
    int maxDigit = 0, digit;
    for(int i = 0; i < ARRAY_SIZE; i++){
        digit = 0;
        for(int j = arr[i]; j > 0; j /= 10){
            digit++;
        }
        if (maxDigit < digit) {
            maxDigit = digit; 
        }
        
    }
    return maxDigit;
}

int pow(int base, int n){
    int res = base;
    for(int i=0;i<n;i++){
        res *= n;
    }
    return res;
}

void shuffleArray(int arr[ARRAY_SIZE]){
    mt19937 randset(rd());
    uniform_int_distribution<int> rnd(0,ARRAY_SIZE);

    for (int i=0;i<ARRAY_SIZE;i++){
        int index1 = rnd(randset);
        int index2 = rnd(randset);

        swap(arr[index1], arr[index2]);
    }
}