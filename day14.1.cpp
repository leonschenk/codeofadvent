#include <iostream>
#include <fstream>
#include <stack>
#include <set>
#include <map>
#include <algorithm>
#include <cmath>
#include <cstring>

struct todo {
    int depth;
    char first;
    char second;
};

std::map<std::pair<char, char>, char> rules;

void execute(int depth, char first, char second, std::map<char, int>& aantallen) {
    if (depth) {
        char insert = rules[{first, second}];
        aantallen[insert]++;
        execute(depth - 1, first, insert, aantallen);
        execute(depth - 1, insert, second, aantallen);
    }
}

int main(void){
    std::ifstream infile("File20");
    
    std::string startposition;
    infile >> startposition;

    char first, second, a, right;
    while (infile >> first >> second >> a >> a >> right) {
        rules[{first, second}] = right;
    }

    std::map<char, int> aantallen;
    for (int i = 0; i < startposition.size(); i++) {
        aantallen[startposition[i]]++;
    }
    for (int i = 0; i < startposition.size() - 1; i++) {
        execute(10, startposition[i], startposition[i+1], aantallen);
    }

    int high = -1, low = -1;
    for (auto i : aantallen) {
        if (high == -1) {
            low = i.second;
            high = i.second;
        } else if (i.second > high) {
            high = i.second;
        } else if (i.second < low) {
            low = i.second;
        }
        std::cout << i.first << ": " << i.second << std::endl;
    }
    std::cout << "High: " << high << " Low: " << low << " result: " << high - low <<std::endl;
}
