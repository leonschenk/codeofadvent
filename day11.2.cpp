#include <iostream>
#include <fstream>
#include <stack>
#include <map>
#include <algorithm>
#include <cmath>
#include <cstring>

const int columns = 10;
const int rows = 10;

char grid[columns][rows];

int increment(int x, int y) {
    if (x < 0 || x >= columns) {
        return 0;
    } else if (y < 0 || y >= rows) {
        return 0;
    } else if (grid[x][y] <= '9' && grid[x][y]++ == '9') {
        return increment(x-1, y-1) + increment(x-1, y) + increment(x-1, y+1) + increment(x, y-1) + increment(x, y+1) + increment(x+1, y-1) + increment(x+1, y) + increment(x+1, y+1) + 1;
    } else {
        return 0;
    }
}

int main(void){
    std::ifstream infile("File14");
    
    char a;
    for (int i = 0; i < columns; i++) {
        for (int j=0; j < columns; j++) {
            infile >> grid[i][j];
            std::cout << grid[i][j];
        }
        std::cout << std::endl;
    }

    int sparks = 0;
    for (int i = 0; true; i++) {
        sparks = 0;
        for (int j = 0; j < columns; j++) {
            for (int k = 0; k < rows; k++) {
                sparks += increment(j, k);
            }
        }
        for (int j = 0; j < columns; j++) {
            for (int k = 0; k < rows; k++) {
                if (grid[j][k] > '9') {
                    grid[j][k] = '0';
                }
            }
        }
        if (sparks == (columns * rows)) {
            sparks = i + 1;
            break;
        }
    }
    std::cout << std::endl;
    for (int i = 0; i < columns; i++) {
        for (int j=0; j < columns; j++) {
            std::cout << grid[i][j];
        }
        std::cout << std::endl;
    }

    
    std::cout << std::endl << sparks << std::endl;
}
