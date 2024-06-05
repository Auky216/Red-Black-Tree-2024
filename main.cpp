#include "RBT.h"

int main(){
    RBT<int> tree;

    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(5);
    tree.insert(20);
    tree.insert(30);
    tree.insert(35);
    tree.printInOrder();


    return 0;
}