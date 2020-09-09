#include <stdio.h>
#include "order_statistics.h"

using namespace std;

int main(){

    //creating a random array
    const int n = 24;
    int arr[n];
    init_random_array(arr,n);
    print_array(arr,n);
    int c=0;
    int a = select(arr, 0, n-1, c);
    // printf("A[%d] = %d\n",a, arr[a]);
    print_array(arr, n);
    return 0;
}
