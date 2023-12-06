#include <vector>
#include <string>
#include <set>
#include <sstream>
#include <help.hpp>
#include <array>

struct Card {
    int id;
    std::set<int> winners;
    std::vector<int> numbers;

    int result = 0;

    friend std::istream &operator>>(std::istream &is, Card& game) {
        std::string gameString;
        char colon;

        is >> gameString >> game.id >> colon;
        int i;
        while (is >> i) {
            game.winners.insert(i);
        }
        is.clear();
        is >> colon;
        while(!is.eof()) {
            int number;
            is >> number;
            game.numbers.push_back(number);
            if (game.winners.find(number) != game.winners.end()) {
                if (game.result) {
                    game.result <<= 1;
                } else {
                    game.result = 1;
                }
            }
        }

        return is;
    }
};

int main(int argc, char* argv[]) {
    std::vector<std::string> lines = readFile(argc, argv);

    for (auto& l : lines) {
        std::cout << l << std::endl;
    }
    std::cout << std::endl << std::endl;

    long result = 0;
    for (auto& l : lines) {
        std::stringstream str{l};
        Card c;
        str >> c;
        std::cout << c.id << c.winners.size() << c.numbers.size() << std::endl;
        result += c.result;
    }

    std::cout << "Resultaat is: " << result << std::endl;
    std::cout << std::endl << std::endl << std::endl;
}

