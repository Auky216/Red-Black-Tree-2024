#include "RBT.h"

using namespace std;

int main(){
    RBT<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(15);
    tree.insert(25);
    tree.insert(24);
    tree.insert(24);
    
    cout<< tree.printInOrder();

    cout<<endl;


    cout<<tree.height()<<ednl;

    cout<< tree.printInOrder();

}