#include "RBT.h"
#include "vector"
using namespace std;

int main(){
    RBT<int> tree;
    
    vector<int> vec;
    for(int i = 0;i<1000000;i++){
        vec.push_back(i);
        tree.insert(i);

    }

    cout<<"------------------------------------------"<<endl;

    for(int i = 1;i<1000000;i++){
        tree.remove(i);

    }

    cout<<"------------------------------------------"<<endl;

    cout<<tree.printInOrder();





}
