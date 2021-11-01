#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
int count=0;
int total_avg_run = 10000;
float KC_Count = 0, KC_Count_Merge = 0;

void InsertSort(int *arr, int start, int end);
void Merge(int array[], int arrayone_index, int mid, int end);
void HybridSort(int arr[],int start,int end, int S);
void Hybrid_Sort(int arr[],int end, int S);
void MergeSort(int arr[],int start,int end);
void Merge1(int array[], int arrayone_index, int mid, int end);
void MergeSort1(int arr[],int start,int end);
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

void PrintArray(int arr[], int array_size){
    for (int i = 0; i < array_size; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
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

int main(){
    int N;
    srand(time(0));
    printf("Enter the size of Array, N: ");
    scanf("%d", &N);

    int S = 22;
    float total_time_hs = 0, total_time_ms = 0;
    for (int i=0; i<total_avg_run; i++){
        int hs_array[N];//Create array
        int ms_array[N]; //Create MergeSort Array
        for (int f=0;f<N;f++) hs_array[f]=rand(); //random array generator
        for (int f=0;f<N;f++) ms_array[f]=hs_array[f]; //Copy hs array into ms array for fairness

        // for Hybrid_Sort//
        clock_t t;
        t=clock();
        Hybrid_Sort(hs_array,N-1, S);
        t = clock() - t;
        total_time_hs += ((float)t)/CLOCKS_PER_SEC; // in second

        // for Merge Sort
        clock_t t1;
        t1=clock();
        MergeSort1(ms_array, 0, N-1);
        t1 = clock() - t1;
        total_time_ms += ((float)t1)/CLOCKS_PER_SEC; // in second
        }
    float avg_KCcount = (float) KC_Count/total_avg_run;
    float avg_KCcount_merge = (float) KC_Count_Merge/total_avg_run;
    float avg_time_hs = total_time_hs/total_avg_run;
    float avg_time_ms = total_time_ms/total_avg_run;
    printf("Hybrid S=%d, Avg Key Comparison = %f, Avg Time = %.10f\n", S, avg_KCcount, avg_time_hs);
    printf("Merge S=%d, Avg Key Comparison = %f, Avg Time = %.10f\n\n", S, avg_KCcount_merge, avg_time_ms);
    KC_Count=0; KC_Count_Merge=0;
    return 0;
}

void InsertSort(int *arr, int start, int end){
    for (int i=start+1;i<=end; i++){
        for (int j=i;j>start; j--)
        {
            KC_Count++;
            if (arr[j]<arr[j-1]){
                int temp =arr[j];
                arr[j] = arr[j-1];
                arr[j-1] = temp;
            }
            else break;
        }
    }
}

void Merge(int array[], int arrayone_index, int mid, int end){
    int arraytwo_index = mid+1;
    while (arrayone_index<=mid && arraytwo_index<=end){ //Iterate thru both array
        KC_Count++;

        if (array[arrayone_index]<array[arraytwo_index]){ //Compare 2nd array to front array
            arrayone_index++; //element of 1st array is smaller than 2nd array. Check next element in 1st array
        }
        else{ //element in first half is bigger or equal than second half
            int value = array[arraytwo_index]; //Temporary storage for later insert
            int trigger_index = arraytwo_index;

            while (trigger_index!=arrayone_index){ //Move all the values to the right
                array[trigger_index] = array[trigger_index-1];
                trigger_index--;
            }
            array[arrayone_index++] = value; //Insert the value that was smaller and update index for next loop
            arraytwo_index++; mid++; //Update the indexes. Mid also update because array shifted
        }


    }
}

void HybridSort(int arr[],int start,int end, int S){
  if(end-start<=S){//less than threshold value, follow InsertionSort
    InsertSort(arr, start, end);
  }
  else
  {
    int middle=(start+end)/2;
    HybridSort(arr,start,middle,S);
    HybridSort(arr,middle+1,end,S);
    Merge(arr,start,middle,end);
  }
}

void Hybrid_Sort(int arr[],int end, int S){
  HybridSort(arr,0,end-1, S);
}

void MergeSort(int arr[],int start,int end){
  if(end-start<=0) return;
  else
  {
    int middle=(start+end)/2;
    MergeSort(arr,start,middle);
    MergeSort(arr,middle+1,end);
    Merge(arr,start,middle,end);
  }
}

void Merge1(int array[], int arrayone_index, int mid, int end){
    int arraytwo_index = mid+1;
    while (arrayone_index<=mid && arraytwo_index<=end){ //Iterate thru both array
        KC_Count_Merge++;

        if (array[arrayone_index]<array[arraytwo_index]){ //Compare 2nd array to front array
            arrayone_index++; //element of 1st array is smaller than 2nd array. Check next element in 1st array
        }
        else{ //element in first half is bigger or equal than second half
            int value = array[arraytwo_index]; //Temporary storage for later insert
            int trigger_index = arraytwo_index;

            while (trigger_index!=arrayone_index){ //Move all the values to the right
                array[trigger_index] = array[trigger_index-1];
                trigger_index--;
            }
            array[arrayone_index++] = value; //Insert the value that was smaller and update index for next loop
            arraytwo_index++; mid++; //Update the indexes. Mid also update because array shifted
        }
    }
}

void MergeSort1(int arr[],int start,int end){
  if(end-start<=0) return;
  else
  {
    int middle=(start+end)/2;
    MergeSort1(arr,start,middle);
    MergeSort1(arr,middle+1,end);
    Merge1(arr,start,middle,end);
  }
}
