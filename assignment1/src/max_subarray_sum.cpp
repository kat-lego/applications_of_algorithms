#include "max_subarray_sum.h"
#include "stdio.h"

void brute(int* arr, int l, int r, max_t& max){
    int n=r-l+1; //get length of the subarray

    arr+=l; //shift the pointer so that index 0 is l

    int sum[n+1]; // an array with cummulitive sums
    sum[0] = 0;
    for(int i=1 ;i< n+1; i++) sum[i]=sum[i-1]+arr[i-1]; //build the cummulitive sums

    max.set(arr[0], 0, 0); //set the max initialy to the subarray with arr[l] only (remember arr has been shifted)

    int s;

    // try the possible options
    for(int i=0 ;i<n ;i++){
        for(int j=0; j<=i; j++){
            s = sum[i+1]-sum[j]; //sum for subarray from j to i
            if(s>max.value){
                max.set(s,j,i);
            }
        }
    }

    max.set(max.value, max.l+l, max.r+l); //account for the shifting

}

void kadane(int* arr, int l, int r, max_t& max){
    int n = r-l+1;

    arr+=l;

    max_t max_p;
    max_p.set(arr[0], 0, 0); //set the local max initialy to the subarray with arr[l] only
    max.set(max_p);

    for(int i=1; i<n; i++){
        //check the maximum sub array that ends at index i
        if(max_p.value>0){
            max_p.value+=arr[i];
        }else{
            max_p.value = arr[i];
            max_p.l = i;
        }
        max_p.r = i;

        //update global max
        if(max_p.value > max.value){
            max.set(max_p);
        }
    }

    max.l+=l; //account for the shift we did on top
    max.r+=l;

}

void divide_and_conquer(int* arr, int l, int r, max_t& max){

    //if you a subarray with 1 item
    if(l==r){
        max.set(arr[l], l, l);
        return;
    }

    int mid = (l+r)/2;
    max_t ans_left, ans_right, ans_cross;
    divide_and_conquer(arr, l, mid, ans_left);
    divide_and_conquer(arr, mid+1, r, ans_right);

    //max subarray ending at position mid
    int max_left = arr[mid];
    int k_left = mid;
    int sum = max_left;

    for(int i=mid-1; i>=l; i--){
        sum+=arr[i];
        if(sum > max_left){
            max_left = sum;
            k_left = i;
        }
    }
    
    //max subarray starting at position mid+1
    int max_right = arr[mid+1];
    int k_right = mid+1;
    sum = max_right;

    for(int i=mid+2; i<=r; i++){
        sum+=arr[i];
        if(sum > max_right){
            max_right = sum;
            k_right = i;
        }
    }

    ans_cross.set(max_left+max_right, k_left, k_right);

    max.set(ans_left);
    if(ans_right.value > max.value){
        max.set(ans_right);
    }

    if(ans_cross.value > max.value){
        max.set(ans_cross);
    }
    
}

void max_t::print(){
    printf("sum: %d\tleft: %d\tright: %d\n", value, l, r);
}

void max_t::set(int v, int i, int j){
    value = v;
    l = i;
    r = j;
}

void max_t::set(max_t& t){
    value = t.value;
    l = t.l;
    r = t.r;
}


