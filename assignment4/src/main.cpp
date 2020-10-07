#include <iostream>
#include "tree.h"
#include "utils.h"

using namespace std;

int main(){
    // rb_node::NIL->left = rb_node::NIL;
    // rb_node::NIL->right = rb_node::NIL;
    // rb_node::NIL->parent = rb_node::NIL;

//     rb_tree* tree = new rb_tree();
//     int arr[] = {2, 4, 5, 3, 6, 7, 8, 9};
//     int n = 5;
//     for(int a=0; a < n; a++){
//         tree->rb_insert(a);
//         tree->print();
//     }

//     for(int a = 0; a<n;a++){
//         tree->rb_delete(a);
//         tree->print();
//     }

//     delete tree;

    simulation sim = simulation(50, 10, 20000);
    sim.build_tree_sim();

}
