#include "utils.h"
#include <iostream>
#include <random>
#include <math.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

void simulation::init_array(int* buf, int n){
    for(int i=0;i<n;i++)buf[i]=i;
}

void simulation::shuffle_array(int* buf, int a, int b){
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

void simulation::build_tree(int* input_array, rb_tree* tree, int n){
    for(int i=0;i<n;i++)tree->rb_insert(input_array[i]);
}

void simulation::build_tree_sim(){
    int n = step_size;
    int* input_array = new int[datapoints*step_size];
    init_array(input_array, datapoints*step_size);
    
    double time = 0;
    rb_tree* tree;
    for(int i=0; i<datapoints; i++){
        
        for(int r=0;r<reruns;r++){
            tree = new rb_tree();
            shuffle_array(input_array, 0, n-1);
            auto start = high_resolution_clock::now();
            build_tree(input_array, tree, n);
            auto end = high_resolution_clock::now();
            time += duration_cast<milliseconds>(end-start).count();

            
            
            delete tree;
        }
        time/=reruns;
        cout<<n<<", "<<time<<endl;
        n+=step_size;
    }

    delete[] input_array;
}

void simulation::insert_delete_sim(){
    int n = step_size;
    int* input_array = new int[datapoints*step_size];
    init_array(input_array, datapoints*step_size);
    
    double time = 0;
    double time2 = 0;
    rb_tree* tree;
    for(int i=0; i<datapoints; i++){
        
        for(int r=0;r<reruns;r++){
            tree = new rb_tree();
            shuffle_array(input_array, 0, n-1);
            auto start = high_resolution_clock::now();
            auto end = high_resolution_clock::now();
            time += duration_cast<milliseconds>(end-start).count();
            
            delete tree;
        }
        time/=reruns;
        cout<<n<<", "<<time<<endl;
        n+=step_size;
    }

    delete[] input_array;
}