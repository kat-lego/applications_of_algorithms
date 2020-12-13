#include "utils.h"
#include <cstdlib>
#include <ctime>
#include <stdio.h>

#define RANGE 50

void get_random_array(int* buf, int n){
    srand(time(0));
    for(int i=0;i<n;i++){
        buf[i] = (rand()%RANGE)-(rand()%RANGE);
    }
}

void print_array(int* arr, int n){
    printf("[ %d", arr[0]);
    for(int i=1;i<n;i++){
        printf(" ,%d", arr[i]);
    }
    printf(" ]\n");
}