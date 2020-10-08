#include <iostream>
#include "tree.h"
#include "utils.h"

using namespace std;

int main(){
    simulation sim = simulation(50, 20, 20000);
    sim.build_tree_sim();
}
