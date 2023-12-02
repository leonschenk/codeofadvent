#include <help.hpp>
#include <vector>
#include <string>

int main(int argc, char* argv[]) {
    std::vector<std::string> lines = readFile(argc, argv);

    unsigned long count = 0;
    for (auto i = lines.begin(); i != lines.end(); i++) {
        std::cout << (*i) << std::endl;

        auto numbers = "0123456789";

        auto j = i->find_first_of(numbers);
        auto k = i->find_last_of(numbers);

        int least = j;
        int most = k;
        int leastVal = i->at(j) - '0';
        int mostVal = i->at(k) - '0';

        std::cout << "Found " << least << "(" << leastVal << ")" << " and " << most << "(" << mostVal << ") = " << leastVal * 10 << mostVal << std::endl << std::endl;
        count += (leastVal * 10) + (mostVal);
    }

    std::cout << "Resultaat: " << count << std::endl;

    std::cout << std::endl << std::endl << std::endl;
}
