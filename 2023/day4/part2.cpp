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

    long result = 0;
    long copies = 1;

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
                game.result++;
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

    std::vector<Card> cards;
    for (auto& l : lines) {
        std::stringstream str{l};
        Card c;
        str >> c;
        cards.push_back(c);
    }

    long result = 0;
    for (int i = 0; i < cards.size(); i++) {
        std::cout << "Card " << cards[i].id << " " << cards[i].copies << " copies" << std::endl;
        result += cards[i].copies;
        for (int j = 1; j < cards[i].result + 1; j++) {
            cards[i + j].copies += cards[i].copies;
        }
    }

    std::cout << "Resultaat is: " << result << std::endl;
    std::cout << std::endl << std::endl << std::endl;
}

