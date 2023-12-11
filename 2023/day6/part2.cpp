#include <vector>
#include <string>
#include <sstream>
#include <math.h>
#include <help.hpp>

int main(int argc, char* argv[]) {
    std::vector<std::string> lines = readFile(argc, argv);

    std::string timestring, distanceString;

    for (char i : lines[0]) {
        if (i >= '0' && i <= '9') {
            timestring.append({i});
        }
    }
    for (char i : lines[1]) {
        if (i >= '0' && i <= '9') {
            distanceString.append({i});
        }
    }

    std::stringstream timeStream(timestring);
    std::stringstream distanceStream(distanceString);

    long result = 1;

    double time, distance;
    timeStream >> time;
    distanceStream >> distance;

    double D = sqrt(pow(time, 2.0) - 4.0 * distance);
    double d1 = (time - D) * 0.5 + 0.000000001;
    double d2 = (time + D) * 0.5 - 0.000000001;

    long res = long(floor(d2)) - long(ceil(d1)) + 1L;

    std::cout << "Tussenresultaat, tijd: " << time << " afstand: " << distance << " result: " << res << std::endl;
    std::cout << "Determinant: " << D << " range: " << d1 << " tot " << d2 << std::endl;

    result *= res;

    std::cout << "Het resultaat is: " << result << std::endl << std::endl << std::endl;
}