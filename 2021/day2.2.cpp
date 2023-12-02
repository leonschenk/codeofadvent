#include <iostream>
#include <fstream>

int main(void){
    std::ifstream infile("File2");
    
    int a;
    std::string dir;
    int aim = 0, hor = 0, depth = 0;
    while (infile >> dir >> a) {
        switch (dir[0]) {
            case 'u':
                aim -= a;
                break;
            case 'd':
                aim += a;
                break;
            case 'f':
                hor += a;
                depth += (a * aim);
                break;
            default:
                std::cout << "unkown direction: " << dir << std::endl;
        }
    }
    std::cout << "aim: " << aim << "hor: " << hor << " depth: " << depth << " total: " << (hor * depth) << std::endl;
}
