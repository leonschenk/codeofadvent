#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstring>

int main(void){
    std::ifstream infile("File10");
    
    const int columns = 100;
    const int circsize = (columns<<1) + 1;

    int iterators[] = {0, columns - 1, columns, columns + 1, columns << 1};
    int* adjacent[] = {iterators, iterators + 1, iterators + 3, iterators + 4};
    char a[circsize];
    std::fill(a, a + circsize, '~');

    int laatsteIterator = 0;
    int sum = 0;
    for (int laatsteIterator = 0; laatsteIterator < columns; ) {
        if (!(infile >> a[iterators[4]])) {
            laatsteIterator++;
            a[iterators[4]] = '~';
        }
        for (int i = 0; i < 4; i++) {
            if (a[iterators[2]] >= a[*adjacent[i]]) {
                break;
            }
            if (i == 3) {
                sum += a[iterators[2]] - '0' + 1;
            }
        }
        for (int i = 0; i < 5; i++) {
            iterators[i] = (++iterators[i])%circsize;
        }
    }
    std::cout << "Sommatie: " << sum << std::endl;
}
