
#ifndef ORDER_STATISTICS_H
#define ORDER_STATISTICS_H

int randomized_select(int* arr, int a, int b, int i);
int randomized_partition(int* arr, int a,int b);

int deterministic_select(int* arr, int a, int b, int i);
void get_medians(int* arr, int* medians, int a, int b);
void insertion_sort(int* arr,int a, int b);
int deterministic_partition(int* arr, int a,int b, int p);

void swap(int& a, int& b);
void init_array(int* buf, int n);
void random_shuffle(int* buf, int a, int b);
void copy_array(const int* src, int* dest, int a, int b);
void print_array(const int* arr,int n);

#endif