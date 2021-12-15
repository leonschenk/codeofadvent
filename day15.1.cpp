#include <iostream>
#include <fstream>
#include <stack>
#include <set>
#include <map>
#include <algorithm>
#include <cmath>
#include <cstring>

const int columns = 100;
const int rows = 100;

int field[columns][rows];
int distances[columns][rows];

std::pair<int, int> neighborhoed[] = {{1, 0}, {0, 1}};

int calcDistance(int x = 0, int y = 0, std::set<std::pair<int, int>>&& previous = std::set<std::pair<int, int>>()) {
    if (x < 0 || x >= columns) {
        return -1;
    } else if (y < 0 || y >= rows) {
        return -1;
    } else if (x == columns-1 && y == rows-1) {
        return distances[x][y] = field[x][y];
    } else if (previous.contains({x, y})) {
        return -1;
    } else if (distances[x][y] >= 0) {
        return distances[x][y];
    } else {
        int min = -1;
        previous.insert({x, y});
        for (int i = 0; i < 2; i++) {
            int res = calcDistance(x + neighborhoed[i].first, y + neighborhoed[i].second, static_cast<std::set<std::pair<int, int> > &&>(previous));
            if (min < 0 || (res >= 0 && res < min)) {
                min = res;
            }
        }
        previous.erase({x, y});
        if (min >= 0) {
            min += field[x][y];
            distances[x][y] = min;
        }
        return min;
    }
}

int main(void){
    std::ifstream infile("File22");
    
    char a;
    std::fill(&distances[0][0], &distances[columns-1][rows-1] + 1, -1);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            field[j][i] = (infile >> a, a - '0');
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            std::cout << field[j][i];
        }
        std::cout << std::endl;
    }
    
    std::cout << std::endl;
    
    std::cout << "Result: " << calcDistance() - field[0][0] << std::endl << std::endl;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            std::cout << distances[j][i] << " ";
        }
        std::cout << std::endl;
    }
}
