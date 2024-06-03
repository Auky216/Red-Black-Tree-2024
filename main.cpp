#include "RBT.h"

int main(){
    RBT<int> tree;

    tree.insert(10);
    tree.insert(5);
    tree.insert(20);

    tree.printInOrder();
}