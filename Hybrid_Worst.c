#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
int keycomparison = 0;
int total_avg_run = 10000;

void Merge(int arr[], int arrayone_index, int mid, int upper_bound){
    int arraytwo_index = mid+1;
    

    //Iterate thru "Both" array. If cannot iterate, the entire array is ordered.
    while((arrayone_index<=mid) && (arraytwo_index<=upper_bound)) { 
        keycomparison++;
        if (arr[arrayone_index] < arr[arraytwo_index]) { //If element in first array is smaller than 2nd array
            arrayone_index++; //Point to next element of first array
        } 
        else{//1st element of 2nd half smaller or equal, 
            int temp = arr[arraytwo_index]; //save element from 2nd array to insert in first array
            
            for(int i = arraytwo_index; i>arrayone_index; i--) { //Shift first array to right.
                arr[i] = arr[i-1];
            }
            arr[arrayone_index] = temp; //Insert saved element into 1st array/;
            arrayone_index++; arraytwo_index++; //Update arrayone&2pointer for next iteration
            mid++; //Shifted array to right, therefore shift middle line to right also
        }
    }
}

void insertSort(int arr[], int start, int end){
        for (int i = start; i <= end; i++) {//Start from index 1th or similar. We don't compare index 0 and before
            for (int j = i; j > start; j--) { //Compare backward
                keycomparison++;

                if (arr[j] < arr[j-1]){ //Behind will not always be ordered. If ordered, no need further iteration
                    int temp = arr[j]; //Swap operation
                    arr[j] = arr[j-1]; 
                    arr[j-1] = temp;
                } 
                else break;
        }
    } 
}

void HybridSort(int arr[], int start, int end, int S){
    if ((start-end+1) > S){
        int mid = (start+end)/2;
        HybridSort(arr, start, end, S);
        HybridSort(arr, mid+1, end, S);
        Merge(arr, start, mid, end);
    } else {
        insertSort(arr, start, end);
    }
}

int *CreateRandomArray(int array_size){
    srand(time(0)); //True random every run
    int *arr = malloc(sizeof(int*)*array_size);
    for (int i = 0; i<array_size; i++){
        arr[i] = rand(); //Generate random array
    }
    return arr;
}
int *CreateBestArray(int array_size){
    int *arr = CreateRandomArray(array_size);
    
    for (int i = 1; i <= array_size-1; i++) {//Start from index 1th or similar. We don't compare index 0 and before
            for (int j = i; j > 0; j--) { //Compare backward

                if (arr[j] < arr[j-1]){ //Behind will not always be ordered. If ordered, no need further iteration
                    int temp = arr[j]; //Swap operation
                    arr[j] = arr[j-1]; 
                    arr[j-1] = temp;
                } 
                else break;
        }
    } 
    return arr;
}

int *CreateWorstArray(int array_size){
    int *arr = CreateRandomArray(array_size);
    for (int i = 1; i <= array_size-1; i++) {//Start from index 1th or similar. We don't compare index 0 and before
            for (int j = i; j > 0; j--) { //Compare backward

                if (arr[j] > arr[j-1]){ //Behind will not always be ordered. If ordered, no need further iteration
                    int temp = arr[j]; //Swap operation
                    arr[j] = arr[j-1]; 
                    arr[j-1] = temp;
                } 
                else break;
        }
    } 
    return arr;
}

void PrintArray(int arr[], int array_size){
    for (int i = 0; i < array_size; i++){
        printf("%d ", arr[i]);
    }
}

int main(void){
    int N;
    printf("Enter size of N: ");
    scanf("%d", &N);

    for (int i = 0; i<=10; i++){
        int S = pow(2,i);
        float total_time_hs = 0;

        for (int j=0;j<10000;j++){
            int *arr = CreateWorstArray(N); //Randomly create worst case array
            int array[N];
            for (int i = 0; i<N; i++){
                array[i] = arr[i]; //transfer element into array type
            }
            // for Hybrid_Sort//
            clock_t t;
            t=clock();
            HybridSort(array, 0, N-1, S);
            t = clock() - t;
            total_time_hs += ((float)t)/CLOCKS_PER_SEC; // in second
        }
        float avg_KCcount = (float) keycomparison/total_avg_run;
        float avg_time_hs = total_time_hs/total_avg_run;
        printf("At S=%d, Avg Key Comparison for worst case = %f, Avg Time = %.10f\n", S, avg_KCcount, avg_time_hs);
        keycomparison=0;
    }
    
    
}