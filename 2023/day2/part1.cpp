#include <help.hpp>
#include <vector>
#include <string>
#include <sstream>

struct Subset {
    int red = 0;
    int green = 0;
    int blue = 0;
};

struct Game {
    long id;
    std::vector<Subset> hands;

    friend std::istream &operator>>(std::istream &is, Game& game) {
        std::string dontcare;
        char dontcareChar;

        is >> dontcare >> game.id >> dontcareChar;
        Subset s;
        while (!is.eof()) {
            int number;
            std::string color;
            is >> number >> color;
            if (!color.length()) {
                continue;
            }
            switch(color.at(0)) {
                case 'r':
                    s.red = number;
                    break;
                case 'g':
                    s.green = number;
                    break;
                case 'b':
                    s.blue = number;
                    break;
                default:
                    throw std::string("Onbekende kleur gevonden: ").append(color).c_str();
            }
            switch(color.back()) {
                case ',':
                    break;
                case ';':
                    game.hands.push_back(s);
                    s = Subset();
                    break;
                default:
                    game.hands.push_back(s);
            }
        }

        return is;
    }

    friend std::ostream &operator<<(std::ostream &os, Game& game) {
        os << "Game " << game.id << ": ";
        for (auto& hand : game.hands) {
            os << hand.red << " red, " << hand.blue << " blue, " << hand.green << " green; ";
        }

        return os << std::endl;
    }
};

int main(int argc, char* argv[]) {
    std::vector<std::string> lines = readFile(argc, argv);

    std::vector<Game> games;

    for (auto i = lines.begin(); i != lines.end(); i++) {
        std::cout << (*i) << std::endl;
        std::istringstream str(*i);
        Game g;
        str >> g;
        games.push_back(g);
        std::cout << g << std::endl;
    }

    unsigned long count = 0;
    const int maxRed = 12; const int maxGreen = 13; const int maxBlue = 14;
    for (auto& g : games) {
        bool toevoegen = true;
        for (auto& s : g.hands) {
            if (s.red > maxRed || s.green > maxGreen || s.blue > maxBlue) {
                toevoegen = false;
                break;
            }
        }
        if (toevoegen) {
            count += g.id;
        }
    }

    std::cout << "Resultaat: " << count << std::endl;

    std::cout << std::endl << std::endl << std::endl;
}
