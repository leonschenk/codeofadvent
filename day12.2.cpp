#include <iostream>
#include <fstream>
#include <stack>
#include <map>
#include <algorithm>
#include <cmath>
#include <cstring>

struct cave {
    bool start;
    bool end;
    bool large;
    std::vector<cave*> connections;
    
    cave& operator+=(const cave& other) {
        start = other.start;
        end = other.end;
        large = other.large;
        for (cave* con : other.connections) {
            connections.push_back(con);
        }
        return *this;
    }
};

int exploreCave(cave& start, std::vector<cave*>&& visitedCaves = std::vector<cave*>(), bool visitedSmallCaveTwice = false) {
    int sum = 0;
    if (!start.large) {
        visitedCaves.push_back(&start);
    }
    for (cave* child : start.connections) {
        if (child->start) {
        } else if (child->end) {
            sum += 1;
        } else if (child->large || std::find(visitedCaves.begin(), visitedCaves.end(), child) == visitedCaves.end()) {
            sum += exploreCave(*child, static_cast<std::vector<cave*>&&>(visitedCaves), visitedSmallCaveTwice);
        } else if (!visitedSmallCaveTwice) {
            sum += exploreCave(*child, static_cast<std::vector<cave*>&&>(visitedCaves), true);
        }
    }
    if (!start.large) {
        visitedCaves.pop_back();
    }
    return sum;
}

int main(void){
    std::ifstream infile("File16");
    
    std::string line;
    std::map<std::string, cave> nodes;

    while(infile >> line) {
        std::string n1 = line.substr(0, line.find('-'));
        std::string n2 = line.substr(line.find('-') + 1);
        
        nodes[n1] += {n1 == "start", n1 == "end", bool(std::isupper(n1[0])), {&nodes[n2]}};
        nodes[n2] += {n2 == "start", n2 == "end", bool(std::isupper(n2[0])), {&nodes[n1]}};
    }
    
    for (auto i : nodes) {
        std::cout << i.first << " connecties " << (i.second.large ? "groot" : "klein") << " aantal connecties: " << i.second.connections.size() << std::endl;
    }

    int resultaat = exploreCave(nodes["start"]);

    std::cout << "Het aantal paden is: " << resultaat << std::endl;
}
