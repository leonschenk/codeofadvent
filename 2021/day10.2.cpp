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
    std::vector<long> scores;
    while (infile >> line) {
        long score = 0;
        std::stack<char> stack;
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
                        goto endfor;
                    }
                    break;
                case ']':
                    a = stack.top(); stack.pop();
                    if (c != a + 2) {
                        goto endfor;
                    }
                    break;
                case '>':
                    a = stack.top(); stack.pop();
                    if (c != a + 2) {
                        goto endfor;
                    }
                    break;
                case '}':
                    a = stack.top(); stack.pop();
                    if (c != a + 2) {
                        goto endfor;
                    }
                    break;
            }
        }
        while(!stack.empty()) {
            char a = stack.top(); stack.pop();
            long s = a == '(' ? 1 : (a == '[' ? 2 : (a == '{' ? 3 : 4));
            score = (score * 5L) + s;
        }
        scores.push_back(score);
endfor:
        continue;
    }
    
    std::sort(scores.begin(), scores.end());
    std::cout << "Resultaat: " << scores[scores.size() >> 1] << std::endl;
}
