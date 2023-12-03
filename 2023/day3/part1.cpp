#include "help.hpp"

bool checkLine(std::string& line, int position, int length) {
    std::cout << "Checking line " << line << " at " << position << " with length " << length << std::endl;
    int startPosition = position ? 1 : 0;
    std::cout << "Startposition: " << position - startPosition << std::endl;
    std::cout << "Length: " << length + startPosition << std::endl;
    int pos = line.find_first_not_of(".0123456789", position - startPosition);
    if (pos >= 0 && pos <= position + length) {
        std::cout << "Found " << line[pos] << " at " << pos << std::endl;
        return true;
    } else {
        std::cout << "Not found any symbol" << std::endl;
        return false;
    }
}

int main(int argc, char* argv[]) {
    std::vector<std::string> lines = readFile(argc, argv);

    for (auto& l : lines) {
        std::cout << l << std::endl;
    }
    std::cout << std::endl << std::endl;

    long result = 0;
    for (int i = 0; i < lines.size(); i++) {
        std::cout << lines[i] << std::endl;
        int curNum = 0;
        int numberLength = 0;
        bool include = false;
        for (int j = 0; j < lines[i].length(); j++) {
            switch (lines[i][j]) {
                case '.':
                    if (numberLength) {
                        if (include) {
                            std::cout << "This line contains symbol in front of number" << std::endl;
                            result += curNum;
                        // previous line
                        } else if (i >= 1 && checkLine(lines[i-1], j - numberLength, numberLength)) {
                            result += curNum;
                        // next line
                        } else if (i + 1 < lines.size() && checkLine(lines[i+1], j - numberLength, numberLength)) {
                            result += curNum;
                        }
                    }
                    curNum = 0;
                    numberLength = 0;
                    include = false;
                    break;
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
                default:
                    if (numberLength) {
                        result += curNum;
                    }
                    curNum = 0;
                    numberLength = 0;
                    include = true;
                    std::cout << "Symbol found: " << lines[i][j] << std::endl;
                    break;
            }
        }
        if (numberLength) {
            if (include) {
                std::cout << "This line contains symbol in front of number" << std::endl;
                result += curNum;
            // previous line
            } else if (i >= 1 && checkLine(lines[i-1], lines[i].length() - numberLength, numberLength)) {
                result += curNum;
                // next line
            } else if (i + 1 < lines.size() && checkLine(lines[i+1], lines[i].length() - numberLength, numberLength)) {
                result += curNum;
            }
        }
    }

    std::cout << "Resultaat: " << result << std::endl;

    std::cout << std::endl << std::endl << std::endl;
}
