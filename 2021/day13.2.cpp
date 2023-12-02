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
    }
    std::string result = "";
    for (int i = 0; i < 8; i++) {
        std::cout << "Which character is this?: " << std::endl;
        char a;
        for (int j = 0; j < 6; j++) {
            for (int k = (i*5); k < ((i+1)*5); k++) {
                if (paper.contains({k, j})) {
                    std::cout << '*';
                } else {
                    std::cout << ' ';
                }
            }
            std::cout << std::endl;
        }
        std::cin >> a;
        result += a;
        std::cout << std::endl;
    }
    std::cout << "Het resultaat is: " << result << std::endl;
}
