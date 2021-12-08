#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstring>

int main(void){
    std::ifstream infile("File7");

    char str[10];
    int aantal = 0;
    while (!infile.eof()) {
        for (int i = 0; i < 10; i++) {
            // read input
            infile >> str;
        }
        infile >> str;
        for (int i = 0; i < 4; i++) {
            // read output
            infile >> str;
            switch(std::strlen(str)) {
                case 2:
                case 3:
                case 4:
                case 7:
                    aantal++;
            }
        }
    }

    std::cout << "Aantal getallen: " << aantal << std::endl;
}
