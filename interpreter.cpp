#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <stack>
#include <vector>
using namespace std;
int main(int argc, char **argv) {
    if (argc != 2) return 1;
    string code;
    map<int,int> match; {
        ifstream ifs(argv[1]);
        if (not ifs) return 1;
        stack<int> stk;
        char c;
        while (ifs >> c) {
            if (c == '[') stk.push(code.size());
            if (c == ']') {
                if (stk.empty()) return 1;
                match[stk.top()] = code.size();
                match[code.size()] = stk.top();
                stk.pop();
            }
            if (c == '+' or c == ',' or c == '-' or c == '.' or
                c == '<' or c == '>' or c == '[' or c == ']') {
                code += c;
            }
        }
        if (not stk.empty()) return 1;
    }
    vector<uint8_t> mem(300000);
    int pptr = 0;
    int mptr = 0;
    while (pptr < code.size()) {
        switch (code[pptr]) {
            case '+': ++ mem[mptr]; break;
            case '-': -- mem[mptr]; break;
            case '>': ++ mptr; if (mem.size() <= mptr) return 1; break;
            case '<': -- mptr; if (mptr < 0) return 1; break;
            case ',': mem[mptr] = cin.get(); if (not cin) mem[mptr] = -1; break;
            case '.': cout << mem[mptr]; cout.flush(); break;
            case '[': pptr = match[pptr] - 1; break;
            case ']': if (mem[mptr]) pptr = match[pptr]; break;
        }
        pptr += 1;
    }
    return 0;
}
