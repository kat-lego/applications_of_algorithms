
#ifndef MAX_SUBARRAY_SUM_H
#define MAX_SUBARRAY_SUM_H

struct max_t
{
    int value,l,r;

    void print();
    void set(int v, int i, int j);
    void set(max_t& t);
};

void brute(int* arr, int l, int r, max_t& max);
void kadane(int* arr, int l, int r, max_t& max);
void divide_and_conquer(int* arr, int l, int r, max_t& max);


#endif