#include <iostream>
#include <fstream>
#include <stack>
#include <set>
#include <list>
#include <map>
#include <algorithm>
#include <cmath>
#include <cstring>

struct snailfishnumber {
    snailfishnumber() : root(nullptr), unused(&nodepool[0]) {
        std::cout << "Creating snailfishnumber" << std::endl;
        node* prev = &nodepool[63];
        for (int i = 0; i < 64; i++) {
            nodepool[i].parent = prev;
            prev = &nodepool[i];
        }
    }
    
    struct node {
        node* parent;
        node* left;
        node* right;
        int value;
    } nodepool[64];
    
    node* root;
    node* unused;
    
    snailfishnumber& operator+=(const snailfishnumber& other) {
        std::cout << "Adding snailfishnumber" << std::endl;
        if (this->root && other.root) {
            node* newRoot = acquireNode();
            newRoot->left = this->root;
            newRoot->left->parent = newRoot;
            newRoot->right = copyNode(other.root);
            newRoot->right->parent = newRoot;
            this->root = newRoot;
            while(this->reduce(this->root));
        } else {
            this->root = copyNode(other.root);
        }
        return *this;
    }

    long magnitude() const {   
        return magnitude(this->root);
    }
    
private:
    node* const findLeft(node* const from) const {
        for (node* i = from; i->parent; i = i->parent) {
            if (i == i->parent->left) {
                continue;
            } else {
                i = i->parent->left;
                while (i) {
                    if (i->left) {
                        i = i->right;
                    } else {
                        return i;
                    }
                }
            }
        }
        return nullptr;
    }

    node* const findRight(node* const from) const {
        for (node* i = from; i->parent; i = i->parent) {
            if (i == i->parent->right) {
                continue;
            } else {
                i = i->parent->right;
                while (i) {
                    if (i->right) {
                        i = i->left;
                    } else {
                        return i;
                    }
                }
            }
        }
        return nullptr;
    }

    bool explode(node* const n, const int depth = 0) {
        if (n->left && depth >= 4) {
            int toAddLeft = n->left->value;
            int toAddRight = n->right->value;

            node* left = findLeft(n);
            if (left) {
                left->value += toAddLeft;
            }
            node* right = findRight(n);
            if (right) {
                right->value += toAddRight;
            }

            releaseNode(n->left);
            releaseNode(n->right);
            
            n->left = nullptr;
            n->right = nullptr;
            n->value = 0;
            
            return true;
        } else if (n->left) {
            bool hasExploded = false;
            hasExploded |= explode(n->left, depth + 1);
            hasExploded |= explode(n->right, depth + 1);
            return hasExploded;
        } else {
            return false;
        }
    }
    
    bool split(node* const n) {
        if (n->left) {
            if (split(n->left)) {
                return true;
            } else if (split(n->right)) {
                return true;
            } else {
                return false;
            }
        } else {
            if (n->value >= 10) {
                n->left = acquireNode();
                n->left->parent = n;
                n->left->value = (n->value>>1);
                n->right = acquireNode();
                n->right->parent = n;
                n->right->value = ((n->value+1)>>1);
                n->value = 0;
                return true;
            } else {
                return false;
            }
        }
    }

    bool reduce(node* const currentNode) {
        bool hasReduced = explode(this->root);

        hasReduced |= split(this->root);

        return hasReduced;
    }
    
    long magnitude(const node *const currentNode) const {
        if (currentNode && currentNode->left) {
            return (magnitude(currentNode->left)*3) + (magnitude(currentNode->right)<<1);
        } else if (currentNode) {
            return currentNode->value;
        } else {
            return 0;
        }
    }

    node* const acquireNode() {
        return new node();
        // node* firstUnusedNode = unused;
        // unused = firstUnusedNode->parent;
        // firstUnusedNode->parent = nullptr;
        // firstUnusedNode->left = nullptr;
        // firstUnusedNode->right = nullptr;
        // firstUnusedNode->value = 0;
        // return firstUnusedNode;
    }
    
    void releaseNode(node* const node) {
        delete node;
    }
    
    node* copyNode(const node* const other) {
        if (!other) {
            return nullptr;
        }
        
        node* newNode = acquireNode();
        if (other->left) {
            newNode->left = copyNode(other->left);
            newNode->left->parent = newNode;
            newNode->right = copyNode(other->right);
            newNode->right->parent = newNode;
        } else {
            newNode->value = other->value;
        }
        return newNode;
    }
    
    node* inputNode(std::istream& input, node* prev) {
        char a;
        if (!(input >> a)) {
            return nullptr;
        }

        node* currentNode = acquireNode();
        currentNode->parent = prev;
        if (a == '[') {
            currentNode->left = inputNode(input, currentNode);
            input >> a;
            currentNode->right = inputNode(input, currentNode);
            input >> a;
        } else {
            currentNode->value = a - '0';
        }
        return currentNode;
    }

    void printNode(std::ostream& output, node* nodeToPrint) {
        if (!nodeToPrint) {
            return;
        }
        
        if (nodeToPrint->left) {
            output << '[';
            printNode(output, nodeToPrint->left);
            output << ',';
            printNode(output, nodeToPrint->right);
            output << ']';
        } else {
            output << nodeToPrint->value;
        }
    }

    friend std::ostream& operator<<(std::ostream& output, snailfishnumber& number) {
        number.printNode(output, number.root);

        return output;
    }
    
    friend std::istream& operator>>(std::istream& input, snailfishnumber& number) { 
        std::cout << "Reading snailfishnumber" << std::endl;

        number.root = number.inputNode(input, nullptr);
        
        return input;
    }
};

int main(void){
    std::ifstream infile("File27");
    
    snailfishnumber result;
    snailfishnumber number;

    while (infile >> number) {
        std::cout << "  " << result << std::endl;
        std::cout << "+ " << number << std::endl;
        result += number;
        std::cout << "= " << result << std::endl;
    }
    
    std::cout << "Het resultaat is: " << result.magnitude() << std::endl;
}
