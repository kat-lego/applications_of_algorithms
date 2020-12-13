#include <stdio.h>
#include <chrono>
#include "order_statistics.h"

using namespace std;
using namespace std::chrono;

void benchmark(){
    //some settings
    int reruns=30;
    int step_size = 20000;
    int sample_size = 50;

    //setting up the data
    int max_n = step_size*sample_size;
    int* input_arr = new int[max_n];   // input array for randomized select
    int* input_arr2 = new int[max_n];  // input array for select 
    init_array(input_arr, max_n);

    //running the tests
    int input_size = 0;
    double time1, time2;
    int ans1, ans2;

    for(int i =0; i<sample_size;i++){
        input_size+=step_size;
        printf("%d, %d", i, input_size);

        time1 = 0;
        time2 = 0;

        for(int r=0;r<reruns;r++){
            random_shuffle(input_arr, 0, input_size-1);
            copy_array(input_arr, input_arr2, 0, input_size-1);

            // random select
            auto start = high_resolution_clock::now();
            ans1 = randomized_select(input_arr, 0, input_size-1, r%input_size+1);
            auto end = high_resolution_clock::now();
            time1 += duration_cast<milliseconds>(end-start).count();

            //select
            start = high_resolution_clock::now();
            ans2 = deterministic_select(input_arr2, 0, input_size-1, r%input_size+1);
            end = high_resolution_clock::now();
            time2 += duration_cast<milliseconds>(end-start).count();
            
            if(ans1!=ans2){
                printf("Output mismatch\n");
                return;
            }

        }
        
        time1/=reruns;
        time2/=reruns;
        printf(", %f, %f\n", time1, time2);
    }

    delete[] input_arr;
    delete[] input_arr2;
}

int main(){
    //creating a random array
    // const int n = 11;
    // int A[n];
    // init_array(A, n);
    // random_shuffle(A, 0, n-1);

    // printf("Test array for random select\n");
    // print_array(A, n);

    // int i = 3;
    // int ai = randomized_select(A, 0, n-1, i);
    // printf("The %dth smallest number is %d\n\n", i, ai);

    // printf("Test array for select\n");
    // print_array(A, n);
    // ai = deterministic_select(A, 0, n-1, i);
    // printf("The %dth smallest number is %d\n\n", i, ai);

    //Running the bench marks
    benchmark();

}
