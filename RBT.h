#include "iostream"

using namespace std;

template<typename T>
struct Node{
    T data;
    char color;
    Node* parent;
    Node* left;
    Node* right;

    Node(T value){
        this->data = value;
        this->color = 'R';
        this->left = nullptr;
        this->right = nullptr;
    }
};

template<typename T>
class RBT{
private:
    Node<T>* root;

public:

    RBT(){
        this->root = nullptr;
    }

    void insert(T value){
        insert(root,value);
    }

    void printInOrder(){
        printInOrder(root);
    }
private:
    void insert(Node<T>* &node, T value){
        if(node == nullptr){
            node = new Node<T>(value);
        }
        else if(value < node->data){
            insert(node->left,value);
        }
        else if(value > node->data){
            insert(node->right,value);
        }
    }

    void printInOrder(Node<T>* node){
        if(node != nullptr){
            printInOrder(node->left);
            cout<<node->data<<"("<<node->color<<")"<<" ";
            printInOrder(node->right);
        }
    }


};