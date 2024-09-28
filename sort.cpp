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
        case 2: {
            quickSort(arr, 0, ARRAY_SIZE-1);
            break;
        }
        case 3: { // heapSort
            return -1; // 🚧🚧
        }
        case 4: {
            insertionSort(arr);
            break;
        }
        case 5: {
            mergeSort(arr, 0, ARRAY_SIZE-1);
            break;
        }
        case 6: {
            shellSort(arr);
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
        cerr << "\nWarning : The array is not sorted correctly." << endl;
        if(PRINT_ARRAY == true){
            cout << "[";
            for(int i=0;i<ARRAY_SIZE;i++) {
                cout << arr[i] << ", ";
            }
            cout << "]\n";    
        }
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
    if(low >= high) return; // base condition
    
    int left = low;
    int right = high;
    int pivot = selectPivotIdx(arr, left, right);
    int temp;

    while(left <= right)
    {
        while (arr[left] < arr[pivot]) {
            left++;
        }
        while (arr[right] > arr[pivot]){
            right--;
        }
        if (left <= right){
            swap(arr[left], arr[right]);
            left++;
            right--;
        }
    }

    if(right > low)
        quickSort(arr, low, right);
    if(left < high)
        quickSort(arr, left, high);
    


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

//-----------

int selectPivotIdx(int arr[ARRAY_SIZE], int low, int high){
    int p1 = arr[low];
    int p2 = arr[high];
    int p3 = arr[(high + low) / 2];

    if(p2 <= p1 && p1 <= p3 || p3 <= p1 && p1 <= p2) return low;
    else if(p1 <= p2 && p2 <= p3 || p3 <= p2 && p2 <= p1) return high;
    else return (high+low)/2;
    
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

bool testSort(int arr[ARRAY_SIZE]){
    for(int i=0;i<ARRAY_SIZE-1;i++){
        if(arr[i] > arr[i+1]){
            // not sorted correctly
            cout << "[?] { idx " << i << ": " << arr[i] << ", idx " << i+1 << ": " << arr[i+1] << " }\n"<< endl;
            return false;
        }
    }
    return true;
}