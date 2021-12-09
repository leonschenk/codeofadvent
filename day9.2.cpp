#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <cstring>

int main(void){
    std::ifstream infile("File10");
    
    const int columns = 100;
    const int circsize = columns + 1;

    int iterators[] = {0, columns - 1, columns};
    int a[circsize];
    char b;
    std::fill(a, a + circsize, 0);

    std::vector<int> basins;
    int aantal = 0;
    while (infile >> b) {
        if (b == '9') {
            // geen basin
            a[iterators[2]] = 0;
        } else {
            // wel een basin
            if (a[iterators[1]] && (aantal%columns != 0)) {
                int basin = a[iterators[1]];
                a[iterators[2]] = basin;
                basins[basin - 1]++;
                if (a[iterators[0]] && a[iterators[0]] != basin) {
                    // combine basins
                    int andereBasin = a[iterators[0]];
                    basins[basin - 1] += basins[andereBasin - 1];
                    basins[andereBasin - 1] = 0;
                    for (int i = 0; i < circsize; i++) {
                        if (i != iterators[2] && a[i] == andereBasin) {
                            a[i] = basin;
                        }
                    }
                }
            } else if (a[iterators[0]]) {
                a[iterators[2]] = a[iterators[0]];
                basins[a[iterators[2]] - 1]++;
            } else {
                a[iterators[2]] = basins.size() + 1;
                basins.push_back(1);
            }
        }
        for (int i = 0; i < 3; i++) {
            iterators[i] = (++iterators[i])%circsize;
        }
        aantal++;
    }
    std::sort(basins.begin(), basins.end(), std::greater());
    for (int i = 0; i < basins.size(); i++) {
        std::cout << "Basin " << i << " size: " << basins[i] << std::endl;
    }
    std::cout << "Resultaat: " << basins[0] * basins[1] * basins[2] << std::endl;
}
