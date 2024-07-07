#include <iostream>
using namespace std;

template<typename T>
struct Node {
    T data;
    char color;
    Node* parent;
    Node* left;
    Node* right;

    Node(T value) : data(value), color('R'), parent(nullptr), left(nullptr), right(nullptr) {}
};

template<typename T>
class RBT {
private:
    Node<T>* root;

public:
    RBT() : root(nullptr) {}

    void insert(T value) {
        Node<T>* newNode = new Node<T>(value);
        insertNode(newNode);
        insertFixUp(newNode);
    }

    void remove(T value) {
        Node<T>* node = search(root, value);
        if (node != nullptr) {
            deleteNode(node);
        } else {
            cout << "Value not found in the tree." << endl;
        }
    }

    string printInOrder() {
        return printInOrder(root);
    }

    bool search(T value) {
        Node<T>* nodeFound = search(root, value);
        return (nodeFound != nullptr);
    }

private:
    void insertNode(Node<T>* node) {
        Node<T>* parent = nullptr;
        Node<T>* current = root;

        while (current != nullptr) {
            parent = current;
            if (node->data < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        node->parent = parent;

        if (parent == nullptr) {
            root = node;
        } else if (node->data < parent->data) {
            parent->left = node;
        } else {
            parent->right = node;
        }

        node->left = nullptr;
        node->right = nullptr;
        node->color = 'R';
    }

    void insertFixUp(Node<T>* node) {
        while (node != root && node->parent->color == 'R') {
            Node<T>* parent = node->parent;
            Node<T>* grandparent = parent->parent;

            if (parent == grandparent->left) {
                Node<T>* uncle = grandparent->right;
                if (uncle != nullptr && uncle->color == 'R') {
                    parent->color = 'B';
                    uncle->color = 'B';
                    grandparent->color = 'R';
                    node = grandparent;
                } else {
                    if (node == parent->right) {
                        node = parent;
                        rotateLeft(node);
                        parent = node->parent;
                    }
                    parent->color = 'B';
                    grandparent->color = 'R';
                    rotateRight(grandparent);
                }
            } else {
                Node<T>* uncle = grandparent->left;
                if (uncle != nullptr && uncle->color == 'R') {
                    parent->color = 'B';
                    uncle->color = 'B';
                    grandparent->color = 'R';
                    node = grandparent;
                } else {
                    if (node == parent->left) {
                        node = parent;
                        rotateRight(node);
                        parent = node->parent;
                    }
                    parent->color = 'B';
                    grandparent->color = 'R';
                    rotateLeft(grandparent);
                }
            }
        }
        root->color = 'B';
    }

    void rotateLeft(Node<T>* node) {
        Node<T>* rightChild = node->right;
        node->right = rightChild->left;
        if (rightChild->left != nullptr) {
            rightChild->left->parent = node;
        }
        rightChild->parent = node->parent;
        if (node->parent == nullptr) {
            root = rightChild;
        } else if (node == node->parent->left) {
            node->parent->left = rightChild;
        } else {
            node->parent->right = rightChild;
        }
        rightChild->left = node;
        node->parent = rightChild;
    }

    void rotateRight(Node<T>* node) {
        Node<T>* leftChild = node->left;
        node->left = leftChild->right;
        if (leftChild->right != nullptr) {
            leftChild->right->parent = node;
        }
        leftChild->parent = node->parent;
        if (node->parent == nullptr) {
            root = leftChild;
        } else if (node == node->parent->right) {
            node->parent->right = leftChild;
        } else {
            node->parent->left = leftChild;
        }
        leftChild->right = node;
        node->parent = leftChild;
    }

    void deleteNode(Node<T>* node) {
    Node<T>* replace;
    Node<T>* temp = node;
    Node<T>* x;
    char temp_original_color = temp->color;

    if (node->left == nullptr) {
        x = node->right;
        transplant(node, node->right);
    } else if (node->right == nullptr) {
        x = node->left;
        transplant(node, node->left);
    } else {
        temp = minValueNode(node->right);
        temp_original_color = temp->color;
        x = temp->right;

        if (temp->parent == node) {
            if (x) x->parent = temp; // Asegurarse de que x no es nullptr antes de asignarle un padre.
        } else {
            transplant(temp, temp->right);
            temp->right = node->right;
            temp->right->parent = temp;
        }

        transplant(node, temp);
        temp->left = node->left;
        temp->left->parent = temp;
        temp->color = node->color;
    }
    delete node;

    if (temp_original_color == 'B') {
        deleteFixUp(x);
    }
}

    void transplant(Node<T>* u, Node<T>* v) {
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

    void deleteFixUp(Node<T>* node) {
    while (node != root && node != nullptr && node->color == 'B') {
        if (node == node->parent->left) {
            Node<T>* sibling = node->parent->right;
            if (sibling && sibling->color == 'R') {
                sibling->color = 'B';
                node->parent->color = 'R';
                rotateLeft(node->parent);
                sibling = node->parent->right;
            }
            if (sibling && (!sibling->left || sibling->left->color == 'B') && (!sibling->right || sibling->right->color == 'B')) {
                sibling->color = 'R';
                node = node->parent;
            } else {
                if (sibling && sibling->right && sibling->right->color == 'B') {
                    if (sibling->left) sibling->left->color = 'B';
                    sibling->color = 'R';
                    rotateRight(sibling);
                    sibling = node->parent->right;
                }
                if (sibling) sibling->color = node->parent->color;
                node->parent->color = 'B';
                if (sibling && sibling->right) sibling->right->color = 'B';
                rotateLeft(node->parent);
                node = root;
            }
        } else {
            // Simétrico al caso anterior, con 'left' y 'right' intercambiados
            Node<T>* sibling = node->parent->left;
            if (sibling && sibling->color == 'R') {
                sibling->color = 'B';
                node->parent->color = 'R';
                rotateRight(node->parent);
                sibling = node->parent->left;
            }
            if (sibling && (!sibling->right || sibling->right->color == 'B') && (!sibling->left || sibling->left->color == 'B')) {
                sibling->color = 'R';
                node = node->parent;
            } else {
                if (sibling && sibling->left && sibling->left->color == 'B') {
                    if (sibling->right) sibling->right->color = 'B';
                    sibling->color = 'R';
                    rotateLeft(sibling);
                    sibling = node->parent->left;
                }
                if (sibling) sibling->color = node->parent->color;
                node->parent->color = 'B';
                if (sibling && sibling->left) sibling->left->color = 'B';
                rotateRight(node->parent);
                node = root;
            }
        }
    }
    if (node) node->color = 'B';
}

    Node<T>* minValueNode(Node<T>* node) {
        Node<T>* current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    Node<T>* search(Node<T>* node, T value) {
        if (node == nullptr || node->data == value) {
            return node;
        }
        if (value < node->data) {
            return search(node->left, value);
        } else {
            return search(node->right, value);
        }
    }

    string printInOrder(Node<T>* node) {
        if (node == nullptr) {
            return "";
        }
        string result = "";
        result += printInOrder(node->left);
        result += to_string(node->data) + "(" + node->color + ") ";
        result += printInOrder(node->right);
        return result;
    }
};
