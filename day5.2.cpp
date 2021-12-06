#include <iostream>
#include <fstream>

int main(void){
    const int width = 1000;
    const int height = 1000;
    
    std::ifstream infile("File2");
    
    int x0, x1, y0, y1;
    int xdir, ydir, stappen;
    int count[width][height] = {};
    char a;
    while(infile >> x0 >> a >> y0 >> a >> a >> x1 >> a >> y1) {
        xdir = x1 - x0;
        ydir = y1 - y0;
        stappen = abs(xdir) > abs(ydir) ? abs(xdir) : abs(ydir);
        xdir = xdir == 0 ? 0 : xdir < 0 ? -1 : 1;
        ydir = ydir == 0 ? 0 : ydir < 0 ? -1 : 1;
        for (int i = 0; i <= stappen; i++) {
            count[x0 + (xdir * i)][y0 + (ydir * i)]++;
        }
    }
    int sum = 0;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (count[i][j] > 1) {
                sum++;
            }
        }
    }
    std::cout << "resultaat: " << sum << std::endl;
}
