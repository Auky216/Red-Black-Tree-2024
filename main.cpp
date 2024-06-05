#include "RBT.h"

int main(){
    RBT<int> tree;

    tree.insert(10);
    tree.insert(5);
    
    tree.printInOrder();

    cout<<tree.search(20);

    return 0;
}