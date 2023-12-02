#include <iostream>
#include <fstream>

int main(void){
    const int target = 80; // 80

    std::ifstream infile("File4");
    
    int x0;
    char a;
    int number[9] = {};
    int sum = 0;
    while(infile >> x0) {
        number[x0]++;
        sum++;
        infile.ignore();
    }
    for (int i = 1; i <= target; i++) {
        int it = i%7;
        int x = number[it];
        sum += number[8];
        number[it] += number[7];
        number[7] = number[8];
        number[8] = x;
    }
    std::cout << "Resultaat na " << target << " dagen: " << sum << std::endl;
}
