#include "order_statistics.h"
#include <stdio.h>
#include <random>
#include <math.h>

#define GSIZE 5.0 //number of elements in a group for the deterministic 

/**
 * Expected linear complexity
 * Returns the ith order statistic (with 0 based indexing)
 */
int random_select(int* arr, int a, int b, int& i){
    if(a==b){
        return arr[a];
    }

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 generator(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distribution(0, b-a);
    int r = distribution(generator); //the random pivot's index

    int p = partition(arr, a, b, r);
    int k = p-a+1;

    if(i == k)return arr[p];
    else if(i<k) return random_select(arr, a, b-1, i);
    else return random_select(arr, a+1, b, i);
}

/** 
 * Linear Complexity
 * Returns the ith order statistic (with 0 based indexing)
*/
int select(int* arr, int a, int b, int& i){
    if(a==b){
        return arr[a];
    }
    
    int num_groups = ceil( (b-a+1)/GSIZE );
    int* medians = new int[num_groups];
    get_medians(arr, medians, a, b);
    int med = num_groups/2;
    int medOfmed = select(medians, 0, num_groups-1, med);
    delete[] medians;

    int p = partition(arr, a, b, medOfmed);
    int k = p-a+1;

    if(i == k)return arr[p];
    else if(i<k) return random_select(arr, a, b-1, i);
    else return random_select(arr, a+1, b, i);
}

/**
 * Partitions arr around r as the pivot
 */
int partition(int* arr, int a,int b, int r){
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

/**
 * Get medians of the groups of 5 elements
 */
void get_medians(int* arr, int* medians, const int& a, const int& b){
    
    int ga,gb,n,index;
    n = b-a+1;
    ga=a;
    index = 0;
    while(ga<b){
        gb = ga+GSIZE;
        gb = (n<gb)?n:gb;
        insertion_sort(arr,ga,gb-1);
        medians[index] = arr[(ga+gb)/2];
        ga = gb;
        index++;
    }

}

void insertion_sort(int* arr,const int& a, const int& b){
    
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

void swap(int& a, int& b){
    int buf = a;
    a = b;
    b = buf;
}

void init_random_array(int* buf, int n){
    int tmp, r;

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 generator(rd()); //Standard mersenne_twister_engine seeded with rd()
    
    for(int i=0;i<n;i++)buf[i]=i;
    
    for(int i=0;i<n;i++){
        std::uniform_int_distribution<> distribution(i, n-1);

        r = distribution(generator);
        tmp = buf[i];
        buf[i] = buf[r];
        buf[r] = tmp;
    }
}

void copy_array(int* src, int* dest, int n){
    for(int i=0;i<n;i++)dest[i]=src[i];
}

void print_array(int* arr, int n){
    printf("[ %d", arr[0]);
    for(int i=1;i<n;i++){
        printf(" ,%d", arr[i]);
    }
    printf(" ]\n");
}