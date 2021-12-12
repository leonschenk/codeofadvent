#include <iostream>
#include <fstream>
#include <stack>
#include <map>
#include <algorithm>
#include <cmath>
#include <cstring>

struct node {
    std::string name;
    bool large;
    std::vector<node*> connections;
    
    node& operator+=(const node& other) {
        name = other.name;
        large = other.large;
        for (node* con : other.connections) {
            connections.push_back(con);
        }
        return *this;
    }
};

struct pathElement {
    pathElement* previous;
    node* currentNode;
    bool visitedSmallCaveTwice;
    std::vector<pathElement> children;
};

int explorePathElement(pathElement& pe, node* startNode, node* endNode) {
    if (pe.currentNode == endNode) {
        return 1;
    }
    for (node* child : pe.currentNode->connections) {
        if (child->large) {
            pe.children.push_back({&pe, child, pe.visitedSmallCaveTwice});
        } else {
            int hasVisited = 0;
            for (pathElement* prev = pe.previous; prev != nullptr; prev = prev->previous) {
                if (prev->currentNode == child) {
                    hasVisited++;
                }
            }
            if (hasVisited == 0 || (hasVisited == 1 && !pe.visitedSmallCaveTwice && child != startNode)) {
                pe.children.push_back({&pe, child, hasVisited == 1 || pe.visitedSmallCaveTwice});
            }
        }
    }
    int sum = 0;
    for (pathElement& child : pe.children) {
        sum += explorePathElement(child, startNode, endNode);
    }
    return sum;
}

int main(void){
    std::ifstream infile("File16");
    
    std::string line;
    std::map<std::string, node> nodes;

    while(infile >> line) {
        std::string n1 = line.substr(0, line.find('-'));
        std::string n2 = line.substr(line.find('-') + 1);
        
        nodes[n1] += {n1, bool(std::isupper(n1[0]))};
        nodes[n2] += {n2, bool(std::isupper(n2[0]))};
        
        nodes[n1].connections.push_back(&nodes[n2]);
        nodes[n2].connections.push_back(&nodes[n1]);
    }
    
    for (auto i : nodes) {
        std::cout << i.first << " connecties " << (i.second.large ? "groot" : "klein") << " aantal connecties: " << i.second.connections.size() << std::endl;
    }

    node* startNode = &nodes["start"];
    pathElement startElement = {nullptr, &nodes["start"], false};
    int resultaat = explorePathElement(startElement, &nodes["start"], &nodes["end"]);

    std::cout << resultaat << std::endl;    
}
