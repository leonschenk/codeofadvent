#include <iostream>
#include <fstream>
#include <stack>
#include <set>
#include <list>
#include <map>
#include <algorithm>
#include <cmath>
#include <cstring>

const int columns = 100;
const int rows = 100;
const int size = 5;

int field[columns*size][rows*size];

int distances[columns*size][rows*size];
enum : int {
    ONBEKEND = 0,
    IN_BEHANDELING = 1,
    DEFINITIEF = 2,
} definitief[columns*size][rows*size] = {};

std::pair<int, int> neighborhoed[] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int main(void){
    std::ifstream infile("File22");
    
    char a;
    std::fill(&distances[0][0], &distances[columns*size-1][rows*size-1] + 1, -1);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            field[j][i] = (infile >> a, a - '0');
            for (int k = 0; k < size; k++) {
                for (int l = 0; l < size; l++) {
                    field[(l*columns) + j][(k*rows) + i] = ((field[j][i] + k + l - 1) % 9) + 1;
                }
            }
        }
    }
    
    definitief[0][0] = DEFINITIEF;
    definitief[0][1] = IN_BEHANDELING;
    definitief[1][0] = IN_BEHANDELING;
    
    std::list<std::pair<int, int>> inBehandeling = {{0, 1}, {1, 0}};

    distances[0][0] = 0;
    distances[0][1] = field[0][1];
    distances[1][0] = field[1][0];
    
    while (definitief[columns*size-1][columns*size-1] != DEFINITIEF) {
        int x;
        int y;
        int dmin = -1;
        for (std::list<std::pair<int, int>>::iterator i = inBehandeling.begin(); i != inBehandeling.end(); i++) {
            if (definitief[i->first][i->second] == DEFINITIEF) {
                i = inBehandeling.erase(i);
            } else if (definitief[i->first][i->second] == IN_BEHANDELING) {
                if (dmin == -1 || distances[i->first][i->second] < dmin) {
                    dmin = distances[i->first][i->second];
                    x = i->first;
                    y = i->second;
                }
            }
        }

        definitief[x][y] = DEFINITIEF;
        for (auto i : neighborhoed) {
            int x1 = x + i.first;
            if (x1 < 0 || x1 > columns * size - 1) {
                continue;
            }
            int y1 = y + i.second;
            if (y1 < 0 || y1 > rows * size - 1) {
                continue;
            }
            auto& d = definitief[x1][y1];
            if (d == DEFINITIEF) {
            } else if (d != IN_BEHANDELING) {
                d = IN_BEHANDELING;
                inBehandeling.push_back({x1, y1});
                distances[x1][y1] = distances[x][y] + field[x1][y1];
            } else {
                int d1 = distances[x1][y1];
                int d2 = distances[x][y] + field[x1][y1];
                distances[x1][y1] = d1 < d2 ? d1 : d2;
            }
        }
    }
    
    std::cout << distances[columns*size-1][columns*size-1] << std::endl;
}
