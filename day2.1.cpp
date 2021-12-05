#include <iostream>
#include <fstream>

int main(void){
    std::ifstream infile("File2");
    
    int a;
    std::string dir;
    int hor = 0, depth = 0;
    while (infile >> dir >> a) {
        switch (dir[0]) {
            case 'u':
                depth -= a;
                break;
            case 'd':
                depth += a;
                break;
            case 'f':
                hor += a;
                break;
            default:
                std::cout << "unkown direction: " << dir << std::endl;
        }
    }
    std::cout << "hor: " << hor << " depth: " << depth << " total: " << (hor * depth) << std::endl;
}
