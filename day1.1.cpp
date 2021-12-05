#include <iostream>
#include <fstream>

int main(void){
    std::ifstream infile("File1");
    
    int a;
    int prev = -1;
    int countIncrements = 0;
    while (infile >> a) {
        if (a > prev && prev >= 0) {
            countIncrements++;
        }
        prev = a;
    }
    std::cout << countIncrements << std::endl;
}
