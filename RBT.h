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
        Node<T>* newNode = new Node<T>(value);
        insert(root, newNode);
        Insert_Fixe_Up(newNode);
    }

    void printInOrder(){
        printInOrder(root);
    }

    bool search(T value){
        Node<T>* nodeFound = search(root,value);
        if(nodeFound == nullptr){
            cout<<"The values was not found"<<endl;
            return false;
        }else{
            return true;
        }
    }
private:

    Node<T>* getParent(Node<T>* node){
        if(node != nullptr){
            return node->parent;
        }else{
            return nullptr;
        }
    }

    Node<T>* getGrandparent(Node<T>* node){
        if(node != nullptr && node->parent != nullptr){
            return node->parent->parent;
        }else{
            return nullptr;
        }
    }

    Node<T>* getUncle(Node<T>* node){
    Node<T>* grandparent = getGrandparent(node);
    if (grandparent == nullptr) {
        return nullptr; 
    }
    if (node->parent == grandparent->left) {
        return grandparent->right; 
    } else {
        return grandparent->left; 
    }
}

    void rotateLeft(Node<T>* node) {
        Node<T> *rightChild = node->right;
        node->right = rightChild->left;

        if (rightChild->left != nullptr) {
            rightChild->left->parent = node;
        }

        rightChild->parent = getParent(node);
        if (getParent(node) == nullptr) {
            root = rightChild;
        } else if (node == getParent(node)->left) {
            getParent(node)->left = rightChild;
        } else {
            getParent(node)->right = rightChild;
        }

        rightChild->left = node;
        node->parent = rightChild;
    }

    void rotateRight(Node<T>* node) {
        Node<T> *leftChild = node->left;
        node->left = leftChild->right;

        if (leftChild->right != nullptr) {
            leftChild->right->parent = node;
        }

        leftChild->parent = getParent(node);
        if (getParent(node) == nullptr) {
            root = leftChild;
        } else if (node == getParent(node)->right) {
            getParent(node)->right = leftChild;
        } else {
            getParent(node)->left = leftChild;
        }

        leftChild->right = node;
        node->parent = leftChild;
    }

    void Insert_Fixe_Up(Node<T>* node){
        while(getParent(node) != nullptr && getParent(node)->color == 'R'){
            if(getParent(node) == getGrandparent(node)->left){
                Node<T>* uncle = getUncle(node);
                if(uncle != nullptr && uncle->color == 'R'){
                    getParent(node)->color = 'B';
                    uncle->color = 'B';
                    getGrandparent(node)->color = 'R';
                    node = getGrandparent(node);
                }else{
                    if(node == getParent(node)->right){
                        node = getParent(node);
                        rotateLeft(node);
                    }
                    getParent(node)->color = 'B';
                    getGrandparent(node)->color = 'R';
                    rotateRight(getGrandparent(node));
                }
            }else{
                Node<T>* uncle = getUncle(node);
                if(uncle != nullptr && uncle->color == 'R'){
                    getParent(node)->color = 'B';
                    uncle->color = 'B';
                    getGrandparent(node)->color = 'R';
                    node = getGrandparent(node);
                }else{
                    if(node == getParent(node)->left){
                        node = getParent(node);
                        rotateRight(node);
                    }
                    getParent(node)->color = 'B';
                    getGrandparent(node)->color = 'R';
                    rotateLeft(getGrandparent(node));
                }
            }
        }

        root->color = 'B';

    }

    Node<T>* search(Node<T>* node,T value) {
        if(node == nullptr || node->data == value){
            return node;
        }

        else if(node->left != nullptr && value < node->left->data){
            return search(node->left,value);
        }
        else if(node->right != nullptr && value > node->right->data){
            return search(node->right,value);
        }

        return nullptr;
    }

    void insert(Node<T>* &node, Node<T>* newNode){
        if(node == nullptr){
            node = newNode;
            newNode->parent = nullptr; 
        } else if(newNode->data < node->data){
            insert(node->left, newNode);
            node->left->parent = node;
        } else if(newNode->data > node->data){
            insert(node->right, newNode);
            node->right->parent = node;
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