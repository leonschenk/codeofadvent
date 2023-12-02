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
    
    std::map<int, std::vector<int>> aantal;

    int vxmin = int(ceil(0.5 * (sqrt(8.0 * double(xmin) + 1.0) - 1.0)));
    int vxmax = int(floor(0.5 * (sqrt(8.0 * double(xmax) + 1.0) - 1.0)));

    std::map<int, std::set<int>> vxenvy;
    for (int vy = ymin; vy < -ymin; vy++) {
        double vyp1 = double(vy<<1) + 1.0;
        int nmin = int(ceil(0.5 * (sqrt((-8.0 * double(ymax)) + (vyp1 * vyp1)) + vyp1)));
        int nmax = int(floor(0.5 * (sqrt((-8.0 * double(ymin)) + (vyp1 * vyp1)) + vyp1)));
        for (int n = nmin; n <= nmax; n++) {
            int vxminkdn = int(ceil((double(xmin)/double(n)) + (0.5 * double(n)) - 0.5));
            int vxmaxkdn = int(floor((double(xmax)/double(n)) + (0.5 * double(n)) - 0.5));
            int m = n < vxmax ? n : vxmax;
            int m2 = vxminkdn <= n ? (n + 1) : vxminkdn;
            
            // alle gevallen met n < Vx
            for (int vx = m2; vx <= vxmaxkdn; vx++) {
                vxenvy[vx].insert(vy);
            }
            // alle gevallen met n >= Vx
            for (int vx = vxmin; vx <= m; vx++) {
                vxenvy[vx].insert(vy);
            }
        }
    }

    int j = 0;
    for (auto i : vxenvy) {
        j += i.second.size();
    }
    
    std::cout << "Aantal totaal: " << j << std::endl;
}
