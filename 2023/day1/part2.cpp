#include <help.hpp>
#include <vector>
#include <string>

struct Paar {
    const char* match;
    int value;
};

int main(int argc, char* argv[]) {
    std::vector<std::string> lines = readFile(argc, argv);

    std::vector<Paar> paren = {
        {.match = "0", .value = 0},
        {.match = "1", .value = 1},
        {.match = "2", .value = 2},
        {.match = "3", .value = 3},
        {.match = "4", .value = 4},
        {.match = "5", .value = 5},
        {.match = "6", .value = 6},
        {.match = "7", .value = 7},
        {.match = "8", .value = 8},
        {.match = "9", .value = 9},
        {.match = "one", .value = 1},
        {.match = "two", .value = 2},
        {.match = "three", .value = 3},
        {.match = "four", .value = 4},
        {.match = "five", .value = 5},
        {.match = "six", .value = 6},
        {.match = "seven", .value = 7},
        {.match = "eight", .value = 8},
        {.match = "nine", .value = 9}
    };

    unsigned long count = 0;
    for (auto i = lines.begin(); i != lines.end(); i++) {
        std::cout << (*i) << std::endl;

        int least = 1000, most = -1;
        int leastVal = 0, mostVal = 0;

        auto numbers = "0123456789";

        for (auto& p : paren) {
            int gevonden = i->find(p.match);
            int laatstgevonden = i->rfind(p.match);
            if (gevonden >= 0 && gevonden < least) {
                least = gevonden;
                leastVal = p.value;
            }
            if (laatstgevonden >= 0 && laatstgevonden > most) {
                most = laatstgevonden;
                mostVal = p.value;
            }
        }

        // auto j = i->find_first_of(numbers);
        // auto k = i->find_last_of(numbers);

        // if (j != least) {
        //     throw "Fout!";
        // }
        // int vatj = i->at(j) - '0';
        // if (vatj != leastVal) {
        //     throw "Fout!";
        // }
        // if (k != most) {
        //     throw "Fout!";
        // }
        // int vatk = i->at(k) - '0';
        // if (vatk != mostVal) {
        //     throw "Fout!";
        // }

        std::cout << "Found " << least << "(" << leastVal << ")" << " and " << most << "(" << mostVal << ") = " << leastVal * 10 << mostVal << std::endl << std::endl;
        count += (leastVal * 10) + (mostVal);
    }

    std::cout << "Resultaat: " << count << std::endl;

    std::cout << std::endl << std::endl << std::endl;
}
