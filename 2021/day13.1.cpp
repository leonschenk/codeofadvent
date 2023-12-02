#include <iostream>
#include <fstream>
#include <stack>
#include <set>
#include <map>
#include <algorithm>
#include <cmath>
#include <cstring>

int main(void){
    std::ifstream infile("File18");
    
    std::string line;
    int x, y;
    char b, d;
    int fold;
    
    std::set<std::pair<int, int>> paper;
    
    while (infile >> x >> b >> y) {
        paper.insert({x, y});
    }
    infile.clear();
    while (infile >> line >> line >> b >> d >> fold) {
        std::vector<std::pair<int, int>> toFold;
        for (auto dot = paper.begin(); dot != paper.end();) {
            bool sw = b == 'x';
            int val = sw ? dot->first : dot->second;
            int otherval = sw ? dot->second : dot->first;
            int newVal = (fold<<1) - val;
            if (val > fold) {
                toFold.push_back({sw ? newVal : otherval, sw ? otherval : newVal});
                dot = paper.erase(dot);
            } else {
                dot++;
            }
        }
        for (auto dot : toFold) {
            paper.insert(dot);
        }
        break;
    }
    std::cout << "Aantal elementen: " << paper.size() << std::endl;
}
