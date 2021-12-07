#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

int main(void){
    std::ifstream infile("File5");
    
    int lijst[1000];
    int aantal = 0;
    int mean = 0;
    int a;
    while (infile >> a) {
        infile.ignore();
        lijst[aantal++] = a;
        mean += a;
    }
    mean /= aantal;

    int fuelm1 = 0;
    int fuelm = 0;
    int fuelp1 = 0;
    for (int i = 0; i < aantal; i++) {
        int d = mean - lijst[i];
        fuelm1 += ((d - 1) * (d - 1)) + abs(d - 1);
        fuelm += (d * d) + abs(d);
        fuelp1 += ((d + 1) * (d + 1)) + abs(d + 1);
    }
    fuelm1 >>= 1;
    fuelm >>= 1;
    fuelp1 >>= 1;
    
    std::cout << "Mean: " << mean << std::endl;
    std::cout << "Aantal: " << aantal << std::endl;
    std::cout << "Amount of fuel required: " << fuelm1 << std::endl;
    std::cout << "Amount of fuel required: " << fuelm << std::endl;
    std::cout << "Amount of fuel required: " << fuelp1 << std::endl;
}
