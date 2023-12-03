#include "help.hpp"
#include <map>

struct Gear {
    bool isGear = false;
    long n1 = 0;
    long n2 = 0;

    void put(long val) {
        if (this->n1 > 0 && this->n2 > 0) {
            if (this->isGear) {
                throw "Gear wordt meerdere malen gebruikt!";
            }
        } else if (this->n1 > 0) {
            this->n2 = val;
        } else {
            this->n1 = val;
        }
    }
};

int main(int argc, char* argv[]) {
    std::vector<std::string> lines = readFile(argc, argv);

    for (auto& l : lines) {
        std::cout << l << std::endl;
    }
    std::cout << std::endl << std::endl;

    std::map<int, std::map<int, Gear>> gears;
    long result = 0;
    for (int i = 0; i < lines.size(); i++) {
        std::cout << lines[i] << std::endl;
        int curNum = 0;
        int numberLength = 0;
        bool include = false;
        for (int j = 0; j < lines[i].length(); j++) {
            switch (lines[i][j]) {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    curNum = (curNum * 10) + (lines[i][j] - '0');
                    numberLength++;
                    std::cout << "Number found, current value: " << curNum << std::endl;
                    break;
                case '*':
                    gears[i][j].isGear = true;
                    std::cout << "Gear found at [" << i << ", " << j << "]" << std::endl;
                default:
                    if (numberLength) {
                        gears[i][j - numberLength - 1].put(curNum);
                        gears[i][j].put(curNum);
                        for (int k = -1; k < numberLength + 1; k++) {
                            gears[i-1][j - numberLength + k].put(curNum);
                            gears[i+1][j - numberLength + k].put(curNum);
                        }
                    }
                    numberLength = 0;
                    curNum = 0;
                    break;
            }
        }
        if (numberLength) {
            gears[i][lines[i].length() - numberLength - 1].put(curNum);
            gears[i][lines[i].length() + 1].put(curNum);
        }
        for (int k = -1; k < numberLength + 1; k++) {
            gears[i-1][lines[i].length() + k].put(curNum);
            gears[i+1][lines[i].length() + k].put(curNum);
        }
    }

    for (auto& i : gears) {
        for (auto& j : i.second) {
            if (j.second.isGear) {
                result += (j.second.n1 * j.second.n2);
            }
        }
    }

    std::cout << "Resultaat: " << result << std::endl;

    std::cout << std::endl << std::endl << std::endl;
}
