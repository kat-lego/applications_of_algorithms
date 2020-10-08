#include <iostream>
#include "tree.h"
#include "utils.h"

using namespace std;

int main(int argc, char* argv[]){
    int d,r,s;
    
    if(argc == 1){
        d = 50;
        r = 20;
        s = 20000;
    }else if(argc == 4){
        d = atoi(argv[1]);
        r = atoi(argv[2]);
        s = atoi(argv[3]);
    }else{
        cout<<"invalid arguments"<<endl;
        exit(0);
    }
    
    simulation sim = simulation(d, r, s);
    sim.build_tree_sim();
}
