#include <iostream>
#include <fstream>
#include <stack>
#include <set>
#include <list>
#include <map>
#include <algorithm>
#include <cmath>
#include <cstring>

int main(void){
    std::ifstream infile("File24");

    std::string a;
    char b;
    int xmin, xmax, ymin, ymax;
    
    infile >> a >> a >> b >> b >> xmin >> b >> b >> xmax >> b >> b >> b >> ymin >> b >> b >> ymax;
    
    int vxmin = int(ceil(0.5 * sqrt(8.0 * xmin + 1.0) - 1.0));
    int vxmax = int(floor(0.5 * sqrt(8.0 * xmax + 1.0) - 1.0));
    
    if (vxmax >= vxmin && ymin < 0) {
        int vy = -ymin;
        int ytop = ((vy * vy) - vy)>>1;
        std::cout << "Het antwoord is: " << ytop << std::endl;
    } else {
        std::cout << "Kan geen output bepalen!" << std::endl;
    }
}
