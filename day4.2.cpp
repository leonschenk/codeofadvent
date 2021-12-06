#include <iostream>
#include <fstream>
#include <math.h>

int main(void){
    std::ifstream infile("File5");
    const int columns = 5;
    const int rows = 5;
    const int indexes = 100;

    int number[indexes];
    int order[indexes];
    for (int i = 0; i < indexes; i++) {
        int a;
        infile >> a;
        number[a] = i;
        order[i] = a;
        infile.ignore();
    }


    int existence[rows][columns];
    int lastWin = 0;
    int resultaat = 0;
    
    while(!infile.eof()) {
        int largestIndex[rows + columns] = {};
        for (int i = 0; i < columns; i++) {
            for (int j = 0; j < rows; j++) {
                int a;
                infile >> a;
                int index = number[a];
                existence[i][j] = index;
                if (index > largestIndex[i]) {
                    largestIndex[i] = index;
                }
                if (index > largestIndex[j + rows]) {
                    largestIndex[j + rows] = index;
                }
            }
        }
        int smallestIndex = indexes;
        for (int i = 0; i < (columns + rows); i++) {
            if (largestIndex[i] < smallestIndex) {
                smallestIndex = largestIndex[i];
            }
        }
        if (smallestIndex > lastWin) {
            lastWin = smallestIndex;
            int sum = 0;
            for (int i = 0; i < columns; i++) {
                for (int j = 0; j < rows; j++) {
                    if (existence[i][j] > smallestIndex) {
                        sum += order[existence[i][j]];
                    }
                }
            }
            resultaat = sum * order[smallestIndex];
        }
    }
    
    std::cout << "laatste getal: " << order[lastWin] << std::endl;
    std::cout << "resultaat: " << resultaat << std::endl;
}
