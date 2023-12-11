#include <vector>
#include <string>
#include <sstream>
#include <math.h>
#include <help.hpp>

int main(int argc, char* argv[]) {
    std::vector<std::string> lines = readFile(argc, argv);

    std::stringstream timeStream(lines[0]);
    std::stringstream distanceStream(lines[1]);

    std::string dontCare;
    timeStream >> dontCare;
    distanceStream >> dontCare;

    std::cout << "Gevonden: " << dontCare << std::endl;

    long result = 1;
    while (!timeStream.eof()) {
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
    }

    std::cout << "Het resultaat is: " << result << std::endl << std::endl << std::endl;
}