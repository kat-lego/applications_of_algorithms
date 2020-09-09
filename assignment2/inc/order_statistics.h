
#ifndef ORDER_STATISTICS_H
#define ORDER_STATISTICS_H

int random_select(int* arr, int a, int b, int& i);
int select(int* arr, int a, int b, int& i);
int partition(int* arr, int a,int b, int r);
void get_medians(int* arr, int* medians, const int& a, const int& b);
void insertion_sort(int* arr,const int& a, const int& b);
void swap(int& a, int& b);
void init_random_array(int* buf, int n);
void copy_array(int* src, int* dest, int n);
void print_array(int* arr, int n);

#endif