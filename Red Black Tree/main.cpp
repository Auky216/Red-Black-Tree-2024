#include "RBT.h"

using namespace std;

int main(){
    RBT<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(15);
    tree.insert(25);
    
    cout<< tree.printInOrder();
}