#ifndef UTILS_H
#define UTILS_H
#include "tree.h"

class simulation{
public:
    void build_tree_sim();
    void insert_delete_sim();

    simulation(int d, int r, int s):
        datapoints(d),
        reruns(r),
        step_size(s)
    {}

private:
    int datapoints;
    int reruns;
    int step_size;

    void build_tree(int* in_array, rb_tree* tree, int n);
    void init_array(int* arr, int n);
    void shuffle_array(int* arr, int a, int b);

};

#endif