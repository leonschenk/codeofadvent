#include <iostream>
#include <fstream>
#include <stack>
#include <set>
#include <list>
#include <map>
#include <algorithm>
#include <cmath>
#include <cstring>

struct file_bits_iterator {
    std::ifstream& infile;
    
    mutable int leftOverBits;
    mutable int aantalLeftOverBits;
    mutable int counter;
    
    file_bits_iterator(std::ifstream& infile) : infile(infile), leftOverBits(0), aantalLeftOverBits(0), counter(0) {
    }
    
    int readNibble() const {
        char a;
        infile >> a;
        int b = a - '0';
        if (b > 9) {
            return b - 7;
        } else {
            return b;
        }
    }
    
    int readBits(int aantal) const {
        int sum = leftOverBits;
        int i = aantalLeftOverBits;
        for (; i < aantal; i += 4) {
            sum = (sum<<4)|readNibble();
        }
        
        aantalLeftOverBits = i - aantal;
        leftOverBits = sum&((1<<aantalLeftOverBits) - 1);
        sum >>= aantalLeftOverBits;
        
        counter += aantal;
        
        return sum;
    }
};

struct packet_iterator {
    file_bits_iterator& file_iterator;

    const enum modeenum : int {
        LEES_AANTAL_BITS = 0,
        LEES_AANTAL_PACKETS = 1
    } mode;
    mutable int counter;

    packet_iterator(file_bits_iterator& file_iterator) : file_iterator(file_iterator), mode(LEES_AANTAL_PACKETS), counter(100000) {
    }

    packet_iterator(file_bits_iterator& file_iterator, modeenum mode, int aantal) : file_iterator(file_iterator), mode(mode), counter(aantal + (mode == LEES_AANTAL_BITS ? file_iterator.counter : 0)) {
    }
    
    long initial(int operation, packet_iterator& it) const {
        switch (operation) {
            case 0:
            std::cout << "0";
            return 0;
            case 1:
            std::cout << "1";
            return 1;
            case 2:
            std::cout << "1000000000000000";
            return 1000000000000000;
            case 3:
            std::cout << "-1000000000000000";
            return -1000000000000000;
            case 5:
            case 6:
            case 7:
            return *it;
            default:
            return 0;
        }
    }

    void print_operation(int operation) const {
        switch (operation) {
            case 0:
            std::cout << " + ";
            break;
            case 1:
            std::cout << " * ";
            break;
            case 2:
            std::cout << " min ";
            break;
            case 3:
            std::cout << " max ";
            break;
            case 5:
            std::cout << " > ";
            break;
            case 6:
            std::cout << " < ";
            break;
            case 7:
            std::cout << " = ";
            break;
        }
    }
    
    long operate(int operation, long a, long b) const {
        switch (operation) {
            case 0:
            return a + b;
            case 1:
            return a * b;
            case 2:
            return a < b ? a : b;
            case 3:
            return a > b ? a : b;
            case 5:
            return a > b ? 1 : 0;
            case 6:
            return a < b ? 1 : 0;
            case 7:
            return a == b ? 1 : 0;
            default:
                std::cout << "error happened" << std::endl;
            return 0;
        }
    }

    bool has_more() const {
        if (mode == LEES_AANTAL_BITS) {
            return file_iterator.counter < counter;
        } else {
            return counter > 0;
        }
    }
    
    int readBits(int aantal) const {
        return file_iterator.readBits(aantal);
    }

    long operator*() const {
        int version = readBits(3);
        int typeID = readBits(3);

        long sum = 0;
        if (typeID == 4) { // literal
            long a = 0;
            int val;
            do {
                val = readBits(5);
                a = (a<<4)|(val&0x0f);
            } while(val&0x10);
            std::cout << a;
            sum = a;
        } else { // operator
            modeenum lengthTypeID = (modeenum)readBits(1);
            int count;
            if (lengthTypeID == LEES_AANTAL_BITS) {
                count = readBits(15);
            } else {
                count = readBits(11);
            }
            std::cout << "([length: " << count << "] ";
            packet_iterator it = packet_iterator(file_iterator, lengthTypeID, count);
            long prev = initial(typeID, it);
            long cur = 0;
            while (it.has_more()) {
                print_operation(typeID);
                
                cur = *it;
                sum = operate(typeID, prev, cur);
                prev = sum;
            }
            std::cout << " === [" << sum << "])";
        }
        
        if (mode == LEES_AANTAL_PACKETS) {
            counter--;
        }

        return sum;
    }
};

int main(void){
    std::ifstream infile("File23");
    
    file_bits_iterator file_iterator(infile);
    
    packet_iterator pi = packet_iterator(file_iterator);
    std::cout << "De waarde is: " << *pi << std::endl;
}
