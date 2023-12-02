#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

int main(void){
    std::ifstream infile("File5");
    
    int lijst[1000];
    int aantal = 0;
    int a;
    while (infile >> a) {
        infile.ignore();
        lijst[aantal++] = a;
    }

    std::sort(lijst, lijst + aantal);

    int median = lijst[aantal >> 1];
    
    int fuel = 0;
    for (int i = 0; i < aantal; i++) {
        fuel += abs(median - lijst[i]);
    }
    
    std::cout << "Amount of fuel required: " << fuel << std::endl;
}
