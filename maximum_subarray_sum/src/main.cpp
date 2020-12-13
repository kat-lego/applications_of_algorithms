#include <stdio.h>
#include <chrono>

#include "utils.h"
#include "max_subarray_sum.h"

using namespace std;
using namespace std::chrono;

void benchmark(){
    //some settings
    int reruns=10;
    int step_size = 10000;
    int sample_size = 50;

    //setting up the data
    int max_n = step_size*sample_size;
    int sample_arr[max_n];
    get_random_array(sample_arr, max_n);

    max_t max[3];

    void (* funs [])(int* arr, int l, int r, max_t& max) = {brute, divide_and_conquer, kadane};


    //running the tests
    int n = 0;
    double time;

    for(int i =0; i<sample_size;i++){
        n+=step_size;
        printf("%d, %d", i, n);

        for(int f=0;f<3;f++){
            time = 0;

            if(!(f==0 && n>150000)) //dont test brute force for large values of n
            for(int r=0;r<reruns;r++){
                auto start = high_resolution_clock::now();
                funs[f](sample_arr, 0, n-1, max[f]);
                auto end = high_resolution_clock::now();
                time += duration_cast<microseconds>(end-start).count();

//                if(f!=0 && max[f].value!=max[f-1].value){
//                    printf("fun %d differs\n", f);
//                    return;
//                }

            }
            time/=reruns;

            printf(", %f", time);

        }
        printf("\n");
    }

}

int main(){
    benchmark();

    return 0;
}
