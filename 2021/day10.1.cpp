#include <iostream>
#include <fstream>
#include <stack>
#include <map>
#include <algorithm>
#include <cmath>
#include <cstring>

int main(void){
    std::ifstream infile("File12");
    
    std::string line;
    int sum = 0;
    while (infile >> line) {
        std::stack<char> stack;
        int score;
        for (const char& c : line) {
            char a;
            switch (c) {
                case '(':
                case '[':
                case '<':
                case '{':
                    stack.push(c);
                    break;
                case ')':
                    a = stack.top(); stack.pop();
                    if (c != a + 1) {
                        score = 3;
                        goto endfor;
                    }
                    break;
                case ']':
                    a = stack.top(); stack.pop();
                    if (c != a + 2) {
                        score = 57;
                        goto endfor;
                    }
                    break;
                case '>':
                    a = stack.top(); stack.pop();
                    if (c != a + 2) {
                        score = 25137;
                        goto endfor;
                    }
                    break;
                case '}':
                    a = stack.top(); stack.pop();
                    if (c != a + 2) {
                        score = 1197;
                        goto endfor;
                    }
                    break;
            }
        }
        continue;
endfor:
        sum += score;
    }

    std::cout << "Resultaat: " << sum << std::endl;
}
