#include <iostream>
#include <fstream>

int main(void){
    std::ifstream infile("File4");
    const int columns = 12;
    
    std::string a;
    int number[columns];
    std::fill(number, number+columns, 0);
    while (infile >> a) {
        for (int i = 0; i < columns; i++) {
            number[i] += (a[i] == '1') ? 1 : -1;
        }
    }
    int gamma = 0;
    for (int i = 0; i < columns; i++) {
        if (number[columns - 1 - i] > 0) {
            gamma += (1<<i);
        }
    }
    int epsilon = ~gamma & ((1 << columns) - 1);
    std::cout << "gamma: " << gamma << std::endl;
    std::cout << "epsilon: " << epsilon << std::endl;
    std::cout << "result: " << gamma * epsilon << std::endl;
}
