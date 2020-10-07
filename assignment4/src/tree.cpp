#include "tree.h"
#include <iostream>

using namespace std;

rb_node* const rb_node::NIL = new rb_node(99999, BLACK);

void rb_tree::rb_insert(int v){
    rb_node* z = new rb_node(v, RED);
    rb_node* y = rb_node::NIL;
    rb_node* x = root;

    while(x!=rb_node::NIL){
        y = x;
        if(z->value < x->value)
            x = x->left;
        else x = x->right;
    }

    z->parent = y;

    if( y == rb_node::NIL)
        root = z;
    else if(z->value < y->value)
        y->left = z;
    else y->right = z;

    rb_insert_fixup(z);

}

void rb_tree::left_rotate(rb_node* x){
    rb_node* y = x->right;
  
    x->right = y->left;
    if( y->left != rb_node::NIL)y->left->parent = x;
    
    y->parent = x->parent;
    if( x->parent == rb_node::NIL)
        root = y;
    else if(x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    
    y->left = x;
    x->parent = y;

}

void rb_tree::right_rotate(rb_node* y){
    rb_node* x = y->left;

    y->left = x->right;
    if(x->right != rb_node::NIL)x->right->parent = y;

    x->parent = y->parent;
    if(y->parent == rb_node::NIL)
        root = x;
    else if(y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;

}

void rb_tree::rb_insert_fixup(rb_node* z){
    rb_node* y;
    while(z->parent->color == RED){
        if(z->parent == z->parent->parent->left){
            y = z->parent->parent->right;
            if(y->color == RED){
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }else{
                if(z == z->parent->right){
                    z = z->parent;
                    left_rotate(z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                right_rotate(z->parent->parent);
            
            }
        }else{
            y = z->parent->parent->left;
            if(y->color == RED){
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }else{
                if(z == z->parent->left){
                    z = z->parent;
                    right_rotate(z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                left_rotate(z->parent->parent);
            
            }
        }
    }

    root->color = BLACK;
}

void rb_tree::rb_transplant(rb_node* u, rb_node* v){
    if(u->parent == rb_node::NIL)
        root = v;
    else if(u == u->parent->left)
        u->parent->left = v;
    else u->parent->right = v;
    v->parent = u->parent;
    u->left = rb_node::NIL;
    u->right = rb_node::NIL;
}

rb_node* rb_tree::binary_search(int v){
    rb_node* x = root;

    while(x!=rb_node::NIL){
        if(v == x->value)
            return x;     
        else if( v < x->value)
            x = x->left;
        else x = x->right;
    }
    return x;
}

rb_node* rb_tree::minimum(rb_node* subtree){
    while (subtree->left != rb_node::NIL)subtree = subtree->left;
    return subtree;
}

void rb_tree::rb_delete(int value){
    rb_node* z = binary_search(value);
    rb_node* y = z;
    rb_node* x;
    int yog = y->color;

    if(z->left == rb_node::NIL){
        x = z->right;
        rb_transplant(z, z->right);
    }else if(z->right == rb_node::NIL){
        x = z->left;
        rb_transplant(z, z->left);
    }else{
        y = minimum(z->right);
        yog = y->color;
        x = y->right;
        if(y->parent == z)
            x->parent = y;
        else{
            rb_transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        rb_transplant(z,y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    delete z;

    if(yog == BLACK)
        rb_delete_fixup(x);        
}

void rb_tree::rb_delete_fixup(rb_node* x){
    rb_node* w;
    while(x != root && x->color == BLACK && x!=rb_node::NIL){
        if(x == x->parent->left){
            w = x->parent->right;

            if(w->color == RED){
                w->color = BLACK;
                x->parent->color = RED;
                left_rotate(x->parent);
                w = x->parent->right;
            }

            if(w->left->color == BLACK && w->right->color == BLACK){
                w->color = RED;
                x = x->parent;
            }else if(w->right->color == BLACK){
                w->left->color = BLACK;
                w->color = RED;
                right_rotate(w);
                w = x->parent->right;
            }

            w->color = x->parent->color;
            x->parent->color = BLACK;
            w->right->color = BLACK;
            left_rotate(x->parent);
            x = root;
        }else{
            w = x->parent->left;

            if(w->color == RED){
                w->color = BLACK;
                x->parent->color = RED;
                right_rotate(x->parent);
                w = x->parent->left;
            }

            if(w->right->color == BLACK && w->left->color == BLACK){
                w->color = RED;
                x = x->parent;
            }else if(w->left->color == BLACK){
                w->right->color = BLACK;
                w->color = RED;
                left_rotate(w);
                w = x->parent->left;
            }

            w->color = x->parent->color;
            x->parent->color = BLACK;
            w->left->color = BLACK;
            right_rotate(x->parent);
            x = root;
        }
    }

    x->color = BLACK;
}


void rb_tree::print(){
    print(root);
    cout<<endl;
}

void rb_tree::print(rb_node* subtree){
    if(subtree == rb_node::NIL)return;
    subtree->print_node();
    print(subtree->left);
    print(subtree->right);
}

void rb_node::print_node(){
    string c = color?"B":"R";
    cout<<"("<<value<<", "<<c<<") ";
}







