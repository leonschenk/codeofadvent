#include <iostream>
#include <fstream>
#include <stack>
#include <map>
#include <algorithm>
#include <cmath>
#include <cstring>

struct cave {
    bool large;
    std::vector<cave*> connections;
    
    cave& operator+=(const cave& other) {
        large = other.large;
        for (cave* con : other.connections) {
            connections.push_back(con);
        }
        return *this;
    }
};

int exploreCave(cave& current, bool visitedSmallCaveTwice = false, std::vector<cave*>&& visitedCaves = std::vector<cave*>()) {
    int sum = 0;
    if (!current.large) {
        visitedCaves.push_back(&current);
    }
    for (cave* child : current.connections) {
        if (child->connections.empty()) {
            sum += 1;
        } else if (child->large || std::find(visitedCaves.begin(), visitedCaves.end(), child) == visitedCaves.end()) {
            sum += exploreCave(*child, visitedSmallCaveTwice, static_cast<std::vector<cave*>&&>(visitedCaves));
        } else if (!visitedSmallCaveTwice) {
            sum += exploreCave(*child, true, static_cast<std::vector<cave*>&&>(visitedCaves));
        }
    }
    if (!current.large) {
        visitedCaves.pop_back();
    }
    return sum;
}

int main(void){
    std::ifstream infile("File16");
    
    std::string line;
    std::map<std::string, cave> caves;

    while(infile >> line) {
        std::string n1 = line.substr(0, line.find('-'));
        std::string n2 = line.substr(line.find('-') + 1);
        
        if (n1 == "start" || n2 == "end") {
            caves[n2] += {bool(std::isupper(n2[0])), {}};
        } else {
            caves[n2] += {bool(std::isupper(n2[0])), {&caves[n1]}};
        } 
        
        if (n2 == "start" || n1 == "end") {
            caves[n1] += {bool(std::isupper(n1[0])), {}};
        } else {
            caves[n1] += {bool(std::isupper(n1[0])), {&caves[n2]}};
        }

    }
    
    for (auto i : caves) {
        std::cout << i.first << " connecties " << (i.second.large ? "groot" : "klein") << " aantal connecties: " << i.second.connections.size() << std::endl;
    }

    int resultaat = exploreCave(caves["start"]);

    std::cout << "Het aantal paden is: " << resultaat << std::endl;
}
