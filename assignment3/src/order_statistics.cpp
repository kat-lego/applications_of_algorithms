#include "order_statistics.h"
#include <stdio.h>
#include <random>
#include <math.h>

#define GSIZE 5.0 //number of elements in a group for the deterministic 

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                           RANDOMIZED SELECT  Í                             //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

int randomized_select(int* arr, int a, int b, int i){
    if(a==b){
        return arr[a];
    }

    int p = randomized_partition(arr, a, b);
    int k = p-a+1;

    if(i == k)return arr[p];
    else if(i<k) return randomized_select(arr, a, p-1, i);
    else return randomized_select(arr, p+1, b, i-k);
}


int randomized_partition(int* arr, int a,int b){

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 generator(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distribution(a, b);
    int r = distribution(generator); //the random pivot's index

    swap(arr[r], arr[b]);

    int i, j;

    int x = arr[b];

    i=a-1;
    for(j=a; j<b; j++){
        if(arr[j]<=x){
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1], arr[b]);
    return i+1;
}


////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                          DETERMINISTIC SELECT  Í                           //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

int deterministic_select(int* arr, int a, int b, int i){
    if(a==b){
        return arr[a];
    }
    
    int num_groups = ceil( (b-a+1)/GSIZE );
    int* medians = new int[num_groups];
    get_medians(arr, medians, a, b);
    int med = num_groups/2;
    int medOfmed = deterministic_select(medians, 0, num_groups-1, med);
    delete[] medians;

    int p = deterministic_partition(arr, a, b, medOfmed);
    int k = p-a+1;

    if(i == k)return arr[p];
    else if(i<k) return deterministic_select(arr, a, p-1, i);
    else return deterministic_select(arr, p+1, b, i-k);
}

void get_medians(int* arr, int* medians, int a, int b){
    int i, start, end;
    int n = (b-a+1)/5;
    for(i=0;i<n;i++){
        start = a+i*GSIZE;
        end = start+GSIZE-1;
        insertion_sort(arr, start, end);
        medians[i] = arr[(start+end)/2];
    }

    if(i*5<b-a+1){
        start = a+i*GSIZE;
        insertion_sort(arr, start, b);
        medians[i] = arr[(start+b)/2];
    }
}

void insertion_sort(int* arr,int a, int b){
    
    int key, j;  
    for (int i = a+1; i <= b; i++){  
        key = arr[i];  
        j = i-1;  

        while (j >= a && arr[j] > key){  
            arr[j+1] = arr[j];  
            j = j-1;  
        }  
        arr[j+1] = key;  
    }  

}

int deterministic_partition(int* arr, int a,int b, int p){

    int r=a;
    while(r<=b && arr[r]!=p)r++;

    swap(arr[r], arr[b]);

    int i, j;

    int x = arr[b];

    i=a-1;
    for(j=a; j<b; j++){
        if(arr[j]<=x){
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1], arr[b]);
    return i+1;
}

////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                              SOME UTILITIES                                //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

void swap(int& a, int& b){
    int buf = a;
    a = b;
    b = buf;
}

void init_array(int* buf, int n){
    for(int i=0;i<n;i++)buf[i]=i;
}

void random_shuffle(int* buf, int a, int b){
    int tmp, r;

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 generator(rd()); //Standard mersenne_twister_engine seeded with rd()
    
    for(int i=a;i<=b;i++){
        std::uniform_int_distribution<> distribution(i, b);

        r = distribution(generator);
        tmp = buf[i];
        buf[i] = buf[r];
        buf[r] = tmp;
    }
}

void copy_array(const int* src, int* dest, int a, int b){
    for(int i=a;i<=b;i++)dest[i]=src[i];
}

void print_array(const int* arr, int n){
    printf("[ %d", arr[0]);
    for(int i=1;i<n;i++){
        printf(" ,%d", arr[i]);
    }
    printf(" ]\n");
}
