#ifndef AVL_H
#define AVL_H

#include <iostream>

class NodeAVL {
public:
    int key;
    NodeAVL* left;
    NodeAVL* right;
    int height;

    NodeAVL(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

class AVL {
public:
    NodeAVL* root;

    AVL() : root(nullptr) {}

    ~AVL() {
        destroyTree(root);
    }

    void destroyTree(NodeAVL* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    int getHeight(NodeAVL* node) {
        return node ? node->height : 0;
    }

    int getBalanceFactor(NodeAVL* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    NodeAVL* rotateRight(NodeAVL* y) {
        NodeAVL* x = y->left;
        NodeAVL* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    NodeAVL* rotateLeft(NodeAVL* x) {
        NodeAVL* y = x->right;
        NodeAVL* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    NodeAVL* insert(NodeAVL* node, int key) {
        if (!node) {
            return new NodeAVL(key);
        }

        if (key < node->key) {
            node->left = insert(node->left, key);
        } else if (key > node->key) {
            node->right = insert(node->right, key);
        } else {
            return node;
        }

        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

        int balanceFactor = getBalanceFactor(node);

        if (balanceFactor > 1) {
            if (key < node->left->key) {
                return rotateRight(node);
            } else {
                node->left = rotateLeft(node->left);
                return rotateRight(node);
            }
        }

        if (balanceFactor < -1) {
            if (key > node->right->key) {
                return rotateLeft(node);
            } else {
                node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
        }

        return node;
    }

    NodeAVL* minValueNodeAVL(NodeAVL* node) {
        NodeAVL* current = node;
        while (current->left != nullptr)
            current = current->left;

        return current;
    }

    NodeAVL* deleteNodeAVL(NodeAVL* root, int key) {
        if (!root) return root;

        if (key < root->key) {
            root->left = deleteNodeAVL(root->left, key);
        } else if (key > root->key) {
            root->right = deleteNodeAVL(root->right, key);
        } else {

            if (!root->left || !root->right) {
                NodeAVL* temp = root->left ? root->left : root->right;

                if (!temp) {
                    temp = root;
                    root = nullptr;
                } else {
                    *root = *temp;
                }

                delete temp;
            } else {
                NodeAVL* temp = minValueNodeAVL(root->right);
                root->key = temp->key;
                root->right = deleteNodeAVL(root->right, temp->key);
            }
        }

        if (!root) return root;

        root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));

        int balanceFactor = getBalanceFactor(root);

        if (balanceFactor > 1) {
            if (getBalanceFactor(root->left) >= 0) {
                return rotateRight(root);
            } else {
                root->left = rotateLeft(root->left);
                return rotateRight(root);
            }
        }

        if (balanceFactor < -1) {
            if (getBalanceFactor(root->right) <= 0) {
                return rotateLeft(root);
            } else {
                root->right = rotateRight(root->right);
                return rotateLeft(root);
            }
        }

        return root;
    }

    NodeAVL* search(NodeAVL* root, int key) {
        if (root == nullptr || root->key == key)
            return root;

        if (root->key < key)
            return search(root->right, key);

        return search(root->left, key);
    }

    void printInOrder(NodeAVL* root) {
        if (root != nullptr) {
            printInOrder(root->left);
            std::cout << root->key << " ";
            printInOrder(root->right);
        }
    }

    void insert(int key) {
        root = insert(root, key);
    }

    void deleteNodeAVL(int key) {
        root = deleteNodeAVL(root, key);
    }

    NodeAVL* search(int key) {
        return search(root, key);
    }

    void printInOrder() {
        std::cout << "In-order traversal: ";
        printInOrder(root);
        std::cout << std::endl;
    }

    int memoryUsage() {
        return memoryUsage(root);
    }

    int memoryUsage(NodeAVL* node) {
        if (node == nullptr) {
            return 0;
        }

        return sizeof(*node) + memoryUsage(node->left) + memoryUsage(node->right);
    }
    int height(NodeAVL* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    int height() {
        return height(root);
    }
};

#endif // AVL_H
