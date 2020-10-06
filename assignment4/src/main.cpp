#include <iostream>
#include "tree.h"

using namespace std;

int main(){
    rb_tree* tree = new rb_tree();
    int arr[] = {2, 4, 5, 2, 6, 7, 8, 9};
    int n;
    for(int a=0; a < 8; a++){
        // cin>>n;
        tree->rb_insert(arr[a]);
        tree->print();
    } 
}
