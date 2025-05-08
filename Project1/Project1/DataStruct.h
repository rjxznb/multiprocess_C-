#pragma
#include<iostream>
using namespace std;


// 双向链表；
template<typename T>
struct ListNode {
    T val;
    ListNode* prev, next;
};

// 头节点；
template<typename T>
struct ListHead {
    ListNode<T>* next;
};


// 红黑树；
enum Color { RED, BLACK };

template<typename Key=int, typename Val=int>
class Node {
public:
    Key data;
    Val val;
    Node* left;
    Node* right;
    Node* parent;
    Color color;

    Node(Key key) : data{ key }, val{NULL}, left(nullptr), right(nullptr), parent(nullptr), color(RED) {}
    Node(Key key, Val val) : data{ key }, val{ val }, left(nullptr), right(nullptr), parent(nullptr), color(RED) {}
};

template<typename Key=int, typename Val=int, typename Pr = std::less<Key>>
class RedBlackTree {
private:
    Node<Key, Val>* root;

    void leftRotate(Node<Key, Val>* node) {
        Node<Key>* rightChild = node->right;
        node->right = rightChild->left;

        if (rightChild->left != nullptr) {
            rightChild->left->parent = node;
        }

        rightChild->parent = node->parent;

        if (node->parent == nullptr) {
            root = rightChild;
        }
        else if (node == node->parent->left) {
            node->parent->left = rightChild;
        }
        else {
            node->parent->right = rightChild;
        }

        rightChild->left = node;
        node->parent = rightChild;
    }

    void rightRotate(Node<Key>* node) {
        Node<Key>* leftChild = node->left;
        node->left = leftChild->right;

        if (leftChild->right != nullptr) {
            leftChild->right->parent = node;
        }

        leftChild->parent = node->parent;

        if (node->parent == nullptr) {
            root = leftChild;
        }
        else if (node == node->parent->right) {
            node->parent->right = leftChild;
        }
        else {
            node->parent->left = leftChild;
        }

        leftChild->right = node;
        node->parent = leftChild;
    }

    void fixInsert(Node<Key, Val>* node) {
        Node<Key, Val>* parent = nullptr;
        Node<Key, Val>* grandparent = nullptr;

        while (node != root && node->parent->color == RED) {
            parent = node->parent;
            grandparent = node->parent->parent;

            if (parent == grandparent->left) {
                Node<Key, Val>* uncle = grandparent->right;

                if (uncle != nullptr && uncle->color == RED) {
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    grandparent->color = RED;
                    node = grandparent;
                }
                else {
                    if (node == parent->right) {
                        leftRotate(parent);
                        node = parent;
                        parent = node->parent;
                    }

                    parent->color = BLACK;
                    grandparent->color = RED;
                    rightRotate(grandparent);
                }
            }
            else {
                Node<Key, Val>* uncle = grandparent->left;

                if (uncle != nullptr && uncle->color == RED) {
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    grandparent->color = RED;
                    node = grandparent;
                }
                else {
                    if (node == parent->left) {
                        rightRotate(parent);
                        node = parent;
                        parent = node->parent;
                    }

                    parent->color = BLACK;
                    grandparent->color = RED;
                    leftRotate(grandparent);
                }
            }
        }

        root->color = BLACK;
    }

    void fixDelete(Node<Key, Val>* node) {
        Node<Key, Val>* sibling;

        while (node != root && node->color == BLACK) {
            if (node == node->parent->left) {
                sibling = node->parent->right;

                if (sibling->color == RED) {
                    sibling->color = BLACK;
                    node->parent->color = RED;
                    leftRotate(node->parent);
                    sibling = node->parent->right;
                }

                if ((sibling->left == nullptr || sibling->left->color == BLACK) &&
                    (sibling->right == nullptr || sibling->right->color == BLACK)) {
                    sibling->color = RED;
                    node = node->parent;
                }
                else {
                    if (sibling->right == nullptr || sibling->right->color == BLACK) {
                        if (sibling->left != nullptr) {
                            sibling->left->color = BLACK;
                        }
                        sibling->color = RED;
                        rightRotate(sibling);
                        sibling = node->parent->right;
                    }

                    sibling->color = node->parent->color;
                    node->parent->color = BLACK;
                    if (sibling->right != nullptr) {
                        sibling->right->color = BLACK;
                    }
                    leftRotate(node->parent);
                    node = root;
                }
            }
            else {
                sibling = node->parent->left;

                if (sibling->color == RED) {
                    sibling->color = BLACK;
                    node->parent->color = RED;
                    rightRotate(node->parent);
                    sibling = node->parent->left;
                }

                if ((sibling->right == nullptr || sibling->right->color == BLACK) &&
                    (sibling->left == nullptr || sibling->left->color == BLACK)) {
                    sibling->color = RED;
                    node = node->parent;
                }
                else {
                    if (sibling->left == nullptr || sibling->left->color == BLACK) {
                        if (sibling->right != nullptr) {
                            sibling->right->color = BLACK;
                        }
                        sibling->color = RED;
                        leftRotate(sibling);
                        sibling = node->parent->left;
                    }

                    sibling->color = node->parent->color;
                    node->parent->color = BLACK;
                    if (sibling->left != nullptr) {
                        sibling->left->color = BLACK;
                    }
                    rightRotate(node->parent);
                    node = root;
                }
            }
        }

        node->color = BLACK;
    }

    Node<Key, Val>* findNode(Node<Key, Val>* root, Key key) {
        while (root != nullptr && root->data != key) {
            if (Pr()(key, root->data)) {
                root = root->left;
            }
            else {
                root = root->right;
            }
        }
        return root;
    }

public:
    RedBlackTree() : root(nullptr) {}

    void insert(Key key, Val val) {
        Node<Key, Val>* newNode = new Node<Key, Val>(key, val);
        Node<Key, Val>* current = root;
        Node<Key, Val>* parent = nullptr;

        while (current != nullptr) {
            parent = current;
            if (Pr()(newNode->data , current->data)) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }

        newNode->parent = parent;

        if (parent == nullptr) {
            root = newNode;
        }
        else if (Pr()(newNode->data,parent->data)) {
            parent->left = newNode;
        }
        else {
            parent->right = newNode;
        }

        fixInsert(newNode);
    }

    void deleteNode(Key key) {
        Node<Key, Val>* node = findNode(root, key);

        if (node == nullptr) {
            return;
        }

        Node<Key, Val>* originalNode = node;
        Color originalColor = originalNode->color;

        Node<Key, Val>* replaceNode;

        if (node->left != nullptr && node->right != nullptr) {
            Node<Key, Val>* successor = node->right;
            while (successor->left != nullptr) {
                successor = successor->left;
            }
            replaceNode = successor;
            originalColor = replaceNode->color;
            node->data = replaceNode->data;
            node = replaceNode;
        }
        else {
            replaceNode = (node->left != nullptr) ? node->left : node->right;
        }

        if (replaceNode != nullptr) {
            replaceNode->parent = node->parent;
        }

        if (node->parent == nullptr) {
            root = replaceNode;
        }
        else if (node == node->parent->left) {
            node->parent->left = replaceNode;
        }
        else {
            node->parent->right = replaceNode;
        }

        if (originalColor == BLACK) {
            fixDelete(replaceNode);
        }

        delete node;
    }

    void search(Key key) {
        Node<Key, Val>* node = findNode(root, key);
        if (node != nullptr) {
            cout << "Found: " << node->data << endl;
        }
        else {
            cout << "Not found" << endl;
        }
    }
    // 中序遍历
    void printTree(Node<Key, Val>* node) {
        if (node != nullptr) {
            printTree(node->left);
            cout << node->data << " (" << (node->color == RED ? "RED" : "BLACK") << ")" << endl;
            printTree(node->right);
        }
    }
    
    void print() {
        printTree(root);
    }
};

