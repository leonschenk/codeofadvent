#include <vector>
#include <string>
#include <set>
#include <sstream>
#include <help.hpp>
#include <array>
#include <algorithm>

struct Range {
    long start;
    long length;

    long end() {
        return this->start + this->length;
    }

    friend std::ostream &operator<<(std::ostream &is, Range& range) {
        is << "[" << range.start << "," << range.end() << ") {";
        // for (int i = 1; i < range.trace.size(); i++) {
        //     is << range.trace[i - 1] << ", ";
        // }
        // if (isTraceSize) {
        //     is << range.trace.back();
        // }
        return is << "}";
    }
};

struct Mapping {
    long destinationStart;
    long sourceStart;
    long length;
    long sourceEnd() {
        return this->sourceStart + this->length;
    }
    long diff() {
        return this->destinationStart - this->sourceStart;
    }

    bool overlaps(Range*& range, std::vector<Range>& mapped, std::vector<Range>& seeds) {
        if (this->sourceEnd() <= range->start) {
            std::cout << std::endl << "(range starts after mapping " << this << ")";
            return false;
        } else if (this->sourceStart >= range->end()) {
            std::cout << std::endl << "(range ends before mapping " << this << ")";
            return false;
        } else if (range->start >= this->sourceStart && range->end() <= this->sourceEnd()) {
            std::cout << std::endl << "(range overlaps completely " << this << ")";
            range->start += this->diff();
            std::cout << " -> " << *range;
            mapped.push_back(*range);
            return true;
        } else if (range->start >= this->sourceStart) {
            std::cout << std::endl << "(range overlaps from the start " << this << ")";
            Range r2 = {.start = range->start + this->diff(), .length = this->sourceEnd() - range->start};
            std::cout << " -> " << r2;
            range->length -= (this->sourceEnd() - range->start);
            range->start = this->sourceEnd();
            std::cout << " % " << *range;
            mapped.push_back(r2);
            return false;
        } else if (range->end() >= this->sourceEnd()) {
            std::cout << std::endl << "(range overlaps at both ends " << this << ")";
            Range r2 = {.start = this->destinationStart, .length = this->length};
            Range r3 = {.start = this->sourceEnd(), .length = range->end() - this->sourceEnd()};
            std::cout << " -> " << r2;
            range->length = this->sourceStart - range->start;
            std::cout << " % " << *range << " & " << r3 << std::endl;
            mapped.push_back(r2);
            seeds.push_back(r3);
            return false;
        } else {
            std::cout << std::endl << "(range overlaps at the end " << this << ")";
            Range r2 = {.start = this->destinationStart, .length = range->end() - this->sourceStart};
            std::cout << " -> " << r2;
            range->length = (this->sourceStart - range->start);
            std::cout << " % " << *range;
            mapped.push_back(r2);
            return false;
        }
    }

    friend std::ostream &operator<<(std::ostream &is, Mapping* mapping) {
        return is << "[" << mapping->sourceStart << "," << mapping->sourceEnd() << ")" << (mapping->diff() >= 0 ? "+" : "") << mapping->diff();
    }
};

int main(int argc, char* argv[]) {
    std::vector<std::string> lines = readFile(argc, argv);

    std::vector<Range> seeds;
    std::vector<Mapping> mappings;
    for (auto& l : lines) {
        // std::cout << l << std::endl;
        if (l.substr(0, 6) == "seeds:") {
            std::cout << "Found seeds in " << l << std::endl;
            std::stringstream str{l.substr(6)};
            while (!str.eof()) {
                Range seed;
                str >> seed.start >> seed.length;
                seeds.push_back(seed);
            }
        } else if (!l.size()) {
            // end mapping
            std::vector<Range> mapped;
            for (int i = 0; i < seeds.size(); i++) {
                Range* seed = &seeds[i];
                std::cout << "Seed " << seeds[i] << std::endl;
                bool isMapped = false;
                for (auto& mapping : mappings) {
                    if (mapping.overlaps(seed, mapped, seeds)) {
                        isMapped = true;
                        break;
                    }
                }
                if (!isMapped) {
                    mapped.push_back(*seed);
                }
                std::cout << std::endl;
            }
            seeds = mapped;
            std::cout << "Mapping done" << std::endl;
        } else if (l.back() == ':') {
            // new mapping
            mappings.clear();
            std::cout << "New mapping: " << std::endl;
        } else {
            Mapping m;
            std::stringstream str{l};
            str >> m.destinationStart >> m.sourceStart >> m.length;
            mappings.push_back(m);
            // std::cout << "Found mapping: " << &m << std::endl;
        }
    }
    if (mappings.size()) {
            // end mapping
            std::vector<Range> mapped;
            for (int i = 0; i < seeds.size(); i++) {
                Range* seed = &seeds[i];
                std::cout << "Seed " << seed;
                bool isMapped = false;
                for (auto& mapping : mappings) {
                    if (mapping.overlaps(seed, mapped, seeds)) {
                        isMapped = true;
                        break;
                    }
                    seed = &seeds[i];
                }
                if (!isMapped) {
                    mapped.push_back(*seed);
                }
                std::cout << std::endl;
            }
            seeds = mapped;
            std::cout << "Mapping done" << std::endl;
    }
    std::cout << std::endl << std::endl;
    for (auto& seed : seeds) {
        std::cout << "seeds: " << seed << std::endl;
    }

    long result = 0;
    std::cout << "Resultaat is: " << std::min_element(seeds.begin(), seeds.end(), [](Range& a, Range& b) -> bool {return a.start < b.start;})->start << std::endl;
    std::cout << std::endl << std::endl << std::endl;
}

