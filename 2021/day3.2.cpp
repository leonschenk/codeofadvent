#include <iostream>
#include <fstream>
#include <math.h>

int main(void){
    std::ifstream infile("File4");
    const int columns = 12;
    const int posses = 1 << (columns - 1);
    
    std::string prefix;
    int number[columns][posses + 1] = {};
    while (infile >> prefix) {
        int a = std::stoi(prefix, 0, 2);
        for (int i = 0; i < columns; i++) {
            int val = a & 1;
            a >>= 1;
            number[columns - 1 - i][a] += (val ? 1 : -1);
            number[i][posses - a]++;
        }
    }
    int oxigen = 0, scrubber = 0;
    for (int i = 0; i < columns; i++) {
        int val1 = number[i][oxigen];
        int count1 = number[columns - 1 - i][posses - oxigen];
        int val2 = number[i][scrubber];
        int count2 = number[columns - 1 - i][posses - scrubber];
        oxigen <<= 1;
        if (count1 == abs(val1)) {
            oxigen += (val1 < 0 ? 0 : 1);
        } else if (val1 >= 0) {
            oxigen += 1;
        }
        scrubber <<= 1;
        if (count2 == abs(val2)) {
            scrubber += (val2 < 0 ? 0 : 1);
        } else if (val2 < 0) {
            scrubber += 1;
        }
        std::cout << count1 << ", " << count2 << std::endl;
    }
    std::cout << "oxigen: " << oxigen << " scrubber: " << scrubber << " result: " << oxigen * scrubber << std::endl;
}
