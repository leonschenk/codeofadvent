#include <iostream>
#include <fstream>

int main(void){
    std::ifstream infile("File1");
    
    int a;
    int prevs[] = {-1, -1, -1};
    int it = 2;
    int countIncrements = 0;
    infile >> prevs[0] >> prevs[1] >> prevs[2];
    while (infile >> a) {
        if (a > prevs[it]) {
            countIncrements++;
        }
        prevs[it] = a;
        it = ((it + 1) % 3);
    }
    std::cout << countIncrements << std::endl;
}
