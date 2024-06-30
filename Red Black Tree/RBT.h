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

    string printInOrder() {
        return printInOrder(root);
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

    void Delete(T value) {
    Node<T>* nodeToDelete = Find(root, value); // Find the node with the given value
    if (nodeToDelete != nullptr) {
        Delete(root, nodeToDelete); // Call the Delete function you implemented earlier
    }

    
private:



void Transplant(Node<T>*& root, Node<T>* u, Node<T>* v) {
    if (u->parent == nullptr) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != nullptr) {
        v->parent = u->parent;
    }
}

Node<T>* Minimum(Node<T>* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

Node<T>* Find(Node<T>* root, T value) {
    if (root == nullptr || root->data == value) {
        // Return the current node if it's either the node we're looking for, or we've reached a leaf node
        return root;
    }
    if (root->data < value) {
        // If the current node's data is less than the value we're looking for, search the right subtree
        return Find(root->right, value);
    } else {
        // If the current node's data is greater than the value we're looking for, search the left subtree
        return Find(root->left, value);
    }
}

    void DeleteFixUp(Node<T>* root, Node<T>* x) {
    while (x != root && x->color == 'B') {
        if (x == x->parent->left) {
            Node<T>* w = x->parent->right;
            if (w->color == 'R') {
                w->color = 'B';
                x->parent->color = 'R';
                rotateLeft(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == 'B' && w->right->color == 'B') {
                w->color = 'R';
                x = x->parent;
            } else {
                if (w->right->color == 'B') {
                    w->left->color = 'B';
                    w->color = 'R';
                    rotateRight(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = 'B';
                w->right->color = 'B';
                rotateLeft(x->parent);
                x = root;
            }
        } else {
            Node<T>* w = x->parent->left;
            if (w->color == 'R') {
                w->color = 'B';
                x->parent->color = 'R';
                rotateRight(x->parent);
                w = x->parent->left;
            }
            if (w->right->color == 'B' && w->left->color == 'B') {
                w->color = 'R';
                x = x->parent;
            } else {
                if (w->left->color == 'B') {
                    w->right->color = 'B';
                    w->color = 'R';
                    rotateLeft(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = 'B';
                w->left->color = 'B';
                rotateRight(x->parent);
                x = root;
            }
        }
    }
    x->color = 'B';
}

    void Delete(Node<T>* root, Node<T>* node) {
        Node<T>* y = node;
        Node<T>* x;
        char yOriginalColor = y->color;

        if (node->left == nullptr) {
            x = node->right;
            Transplant(root, node, node->right);
        } else if (node->right == nullptr) {
            x = node->left;
            Transplant(root, node, node->left);
        } else {
            y = Minimum(node->right);
            yOriginalColor = y->color;
            x = y->right;

            if (y->parent == node) {
                x->parent = y;
            } else {
                Transplant(root, y, y->right);
                y->right = node->right;
                y->right->parent = y;
            }

            Transplant(root, node, y);
            y->left = node->left;
            y->left->parent = y;
            y->color = node->color;
        }

        if (yOriginalColor == 'B') {
            DeleteFixUp(root, x);
        }
    }

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

    string printInOrder(Node<T>* node){
        string result = "";
        if(node != nullptr){
            result += printInOrder(node->left);
            result += to_string(node->data) + "(" + node->color + ")" + " ";
            result += printInOrder(node->right);
        }
        return result;
    }




};