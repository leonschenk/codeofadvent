#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstring>

int main(void){
    std::ifstream infile("File7");

    char str[10];
    int sum = 0;
    while (!infile.eof()) {
        char str1[3] = {};
        char str4[4];
        char str4d1[3] = {};
        for (int i = 0; i < 10; i++) {
            // read input
            infile >> str;
            switch(std::strlen(str)) {
                case 2:
                    str1[0] = str[0];
                    str1[1] = str[1];
                    break;
                case 3:
                    break;
                case 4:
                    str4[0] = str[0];
                    str4[1] = str[1];
                    str4[2] = str[2];
                    str4[3] = str[3];
                    break;
                case 7:
                    break;
                default:
                    break;
            }
        }
        int j = 0;
        for (int i = 0; i < 4; i++) {
            if (str4[i] == str1[0]) {
                continue;
            } else if (str4[i] == str1[1]) {
                continue;
            } else {
                str4d1[j++] = str4[i];
            }
        }
        infile >> str;
        int powi = 1000;
        for (int i = 0; i < 4; i++) {
            // read output
            infile >> str;
            switch(std::strlen(str)) {
                case 2:
                    sum += (1 * powi);
                    break;
                case 3:
                    sum += (7 * powi);
                    break;
                case 4:
                    sum += (4 * powi);
                    break;
                case 5:
                    // 2, 3, 5
                    if (std::strchr(str, str4d1[0]) && std::strchr(str, str4d1[1])) {
                        sum += (5 * powi);
                    } else if (std::strchr(str, str1[0]) && std::strchr(str, str1[1])) {
                        sum += (3 * powi);
                    } else {
                        sum += (2 * powi);
                    }
                    break;
                case 6:
                    // 0, 6, 9
                    if (std::strchr(str, str1[0]) && std::strchr(str, str1[1])) {
                        if (std::strchr(str, str4d1[0]) && std::strchr(str, str4d1[1])) {
                            sum += (9 * powi);
                        } else {
                            sum += (0 * powi);
                        }
                    } else {
                        sum += (6 * powi);
                    }
                    break;
                case 7:
                    sum += (8 * powi);
                    break;
            }
            powi /= 10;
        }
    }
    std::cout << "Sommatie: " << sum << std::endl;
}
