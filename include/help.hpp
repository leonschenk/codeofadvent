#include <iostream>
#include <fstream>
#include <vector>

void printhelp(std::string&& text) {
    std::cout << text << std::endl;
}

std::vector<std::string> readFile(int argc, char* argv[]) {
    if (argc < 2) {
        printhelp("arg 1 is the input filename");
    }

    std::string inputfile = std::string("input/") + std::string(argv[1]);
    std::ifstream input = std::ifstream(inputfile);
    std::vector<std::string> lines;

    for (std::string line; getline(input, line); ) {
        lines.push_back(line);
    }

    input.close();

    return lines;
}
