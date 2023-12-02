#include <iostream>
#include <fstream>
#include <stack>
#include <set>
#include <map>
#include <algorithm>
#include <cmath>
#include <cstring>

std::map<char, int> cToInd;
std::map<int, char> indToC;

const int steps = 40;
const int options = 10;

long cache[2][options][options][options] = {};
int rules[options][options] = {};

int main(void){
    std::ifstream infile("File20");
    
    std::string startposition;
    infile >> startposition;

    // inlezen van de regels en vertalen naar indices
    int curInd = 0;
    char first, second, a, right;
    while (infile >> first >> second >> a >> a >> right) {
        if (!cToInd.contains(first)) {
            cToInd[first] = curInd++;
            indToC[cToInd[first]] = first;
        }
        if (!cToInd.contains(second)) {
            cToInd[second] = curInd++;
            indToC[cToInd[second]] = second;
        }
        if (!cToInd.contains(right)) {
            cToInd[right] = curInd++;
            indToC[cToInd[right]] = right;
        }

        std::cout << cToInd[first] << cToInd[second] << ": " << cToInd[right] << std::endl;
        rules[cToInd[first]][cToInd[second]] = cToInd[right];
    }
    
    // per step alle opties doorrekenen (hoeft slechts 1 stap terug te kijken)
    for (int i = 0; i < steps; i++) {
        int stepIt = i&0x01;
        int prevStepIt = stepIt^0x01;
        for (int j = 0; j < options; j++) {
            for (int k = 0; k < options; k++) {
                // tel bij de getallen het geinserteerde getal plus van de vorige step de geïnserteerde getallen links en rechts
                int insertedAtThisLevel = rules[j][k];
                for (int l = 0; l < options; l++) {
                    cache[stepIt][j][k][l] = cache[prevStepIt][j][insertedAtThisLevel][l] + cache[prevStepIt][insertedAtThisLevel][k][l];
                }
                cache[stepIt][j][k][insertedAtThisLevel]++;
            }
        }
    }

    long res[options] = {};
    for (int i = 0; i < startposition.size(); i++) {
        res[cToInd[startposition[i]]]++;
    }
    for (int i = 0; i < startposition.size() - 1; i++) {
        int ind = cToInd[startposition[i]];
        int ind2 = cToInd[startposition[i+1]];
        // tel alle getallen op van alle paartjes in de startposition
        for (int j = 0; j < options; j++) {
            res[j] += cache[(steps + 1) & 0x01][ind][ind2][j];
        }
    }

    long high = -1, low = -1;
    for (int i = 0; i < options; i++) {
        if (high == -1) {
            low = res[i];
            high = res[i];
        } else if (res[i] > high) {
            high = res[i];
        } else if (res[i] < low) {
            low = res[i];
        }
    }
    
    std::cout << "High: " << high << " and Low: " << low << " Result in: " << high - low << std::endl;
}
