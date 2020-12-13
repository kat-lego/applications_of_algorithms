#ifndef TREE_H
#define TREE_H

#define RED 0
#define BLACK 1

#include <stdio.h>

using namespace std;

class rb_node{
public:    
    
    static rb_node* const NIL;
    rb_node* left = NIL;
    rb_node* right = NIL;
    rb_node* parent = NIL;
    
    int value;
    bool color; // true for black and false for red

    rb_node(int v, bool c) : value(v), color(c) {}
    void print_node();

    ~rb_node() {
        if(this->left != NIL)
            delete left;
        if(this->right != NIL)
            delete right;
    }
};

class rb_tree{
public:
    rb_node* root = rb_node::NIL;

    void rb_insert(int v);
    void rb_insert_fixup(rb_node* z);
    void left_rotate(rb_node* x);
    void right_rotate(rb_node* x);
    void rb_delete(int value);
    void rb_transplant(rb_node* u, rb_node* v);
    rb_node* binary_search(int v);
    rb_node* minimum(rb_node* subtree);
    void rb_delete_fixup(rb_node* x);

    void print(rb_node* subtree);
    void print();

    ~rb_tree(){
        if(root!=rb_node::NIL)
            delete root;
    }

};




#endif
