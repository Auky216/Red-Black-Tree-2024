#include "iostream"

using namespace std;

template<typename T>
struct Node {
    T data;
    char color;
    Node* parent;
    Node* left;
    Node* right;

    Node(T value) {
        this->data = value;
        this->color = 'R';
        this->parent = nullptr;
        this->left = nullptr;
        this->right = nullptr;
    }
};

template<typename T>
class RBT {
private:
    Node<T>* root;

public:
    RBT() {
        this->root = nullptr;
    }

    Node<T>* getRoot() const {
        return root;
    }

    void insert(T value) {
        Node<T>* newNode = new Node<T>(value);
        insert(root, newNode);
        Insert_Fixe_Up(newNode);
    }

    bool deleteNode(T value) {
        Node<T>* nodeToDelete = search(root, value);
        if (nodeToDelete != nullptr) {
            Delete(root, nodeToDelete);
            return true;
        }
        return false;
    }

    std::string printInOrder() {
        return printInOrder(root);
    }

    bool search(T value) {
        Node<T>* nodeFound = search(root, value);
        return nodeFound != nullptr;
    }

    void clear() {
        clear(root);
        root = nullptr;
    }

private:
    void clear(Node<T>* node) {
        if (node == nullptr) {
            return;
        }
        clear(node->left);
        clear(node->right);
        delete node;
    }

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
            return root;
        }
        if (root->data < value) {
            return Find(root->right, value);
        } else {
            return Find(root->left, value);
        }
    }

    void DeleteFixUp(Node<T>*& root, Node<T>* x) {
        while (x != root && x->color == 'B') {
            if (x == x->parent->left) {
                Node<T>* w = x->parent->right;
                if (w->color == 'R') {
                    w->color = 'B';
                    x->parent->color = 'R';
                    rotateLeft(x->parent);
                    w = x->parent->right;
                }
                if ((w->left == nullptr || w->left->color == 'B') && (w->right == nullptr || w->right->color == 'B')) {
                    w->color = 'R';
                    x = x->parent;
                } else {
                    if (w->right == nullptr || w->right->color == 'B') {
                        if (w->left != nullptr) w->left->color = 'B';
                        w->color = 'R';
                        rotateRight(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = 'B';
                    if (w->right != nullptr) w->right->color = 'B';
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
                if ((w->right == nullptr || w->right->color == 'B') && (w->left == nullptr || w->left->color == 'B')) {
                    w->color = 'R';
                    x = x->parent;
                } else {
                    if (w->left == nullptr || w->left->color == 'B') {
                        if (w->right != nullptr) w->right->color = 'B';
                        w->color = 'R';
                        rotateLeft(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = 'B';
                    if (w->left != nullptr) w->left->color = 'B';
                    rotateRight(x->parent);
                    x = root;
                }
            }
        }
        if (x != nullptr) x->color = 'B';
    }

    void Delete(Node<T>*& root, Node<T>* node) {
        Node<T>* y = node;
        Node<T>* x = nullptr;
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

            if (y->parent != node) {
                Transplant(root, y, y->right);
                y->right = node->right;
                if (y->right != nullptr) y->right->parent = y;
            } else if (x != nullptr) {
                x->parent = y;
            }

            Transplant(root, node, y);
            y->left = node->left;
            if (y->left != nullptr) y->left->parent = y;
            y->color = node->color;
        }

        delete node;

        if (yOriginalColor == 'B' && x != nullptr) {
            DeleteFixUp(root, x);
        }
    }

    Node<T>* getParent(Node<T>* node) {
        return node != nullptr ? node->parent : nullptr;
    }

    Node<T>* getGrandparent(Node<T>* node) {
        return (node != nullptr && node->parent != nullptr) ? node->parent->parent : nullptr;
    }

    Node<T>* getUncle(Node<T>* node) {
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
        Node<T>* rightChild = node->right;
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
        Node<T>* leftChild = node->left;
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

    void insert(Node<T>*& root, Node<T>* node) {
        if (root == nullptr) {
            root = node;
        } else {
            if (node->data < root->data) {
                if (root->left != nullptr) {
                    insert(root->left, node);
                } else {
                    root->left = node;
                    node->parent = root;
                }
            } else {
                if (root->right != nullptr) {
                    insert(root->right, node);
                } else {
                    root->right = node;
                    node->parent = root;
                }
            }
        }
    }

    void Insert_Fixe_Up(Node<T>* node) {
        while (node != root && node->parent->color == 'R') {
            if (node->parent == getGrandparent(node)->left) {
                Node<T>* uncle = getUncle(node);
                if (uncle != nullptr && uncle->color == 'R') {
                    node->parent->color = 'B';
                    uncle->color = 'B';
                    getGrandparent(node)->color = 'R';
                    node = getGrandparent(node);
                } else {
                    if (node == node->parent->right) {
                        node = node->parent;
                        rotateLeft(node);
                    }
                    node->parent->color = 'B';
                    getGrandparent(node)->color = 'R';
                    rotateRight(getGrandparent(node));
                }
            } else {
                Node<T>* uncle = getUncle(node);
                if (uncle != nullptr && uncle->color == 'R') {
                    node->parent->color = 'B';
                    uncle->color = 'B';
                    getGrandparent(node)->color = 'R';
                    node = getGrandparent(node);
                } else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        rotateRight(node);
                    }
                    node->parent->color = 'B';
                    getGrandparent(node)->color = 'R';
                    rotateLeft(getGrandparent(node));
                }
            }
        }
        root->color = 'B';
    }

    std::string printInOrder(Node<T>* node) {
        if (node == nullptr) {
            return "";
        }
        std::string result;
        result += printInOrder(node->left);
        result += std::to_string(node->data) + " ";
        result += printInOrder(node->right);
        return result;
    }

    Node<T>* search(Node<T>* node, T value) const {
        if (node == nullptr || node->data == value) {
            return node;
        }
        if (value < node->data) {
            return search(node->left, value);
        } else {
            return search(node->right, value);
        }
    }
};