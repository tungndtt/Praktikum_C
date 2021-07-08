#include "strings.hpp"
#include <stdarg.h>


size_t countAbc(const std::string& input) {
    size_t count = 0;
    for(int i=0; i<input.length(); i++) {
        char c = input[i];
        count += c>='A' && c<='Z' || c >='a' && c<='z'? 1 : 0;
    }
    return count;
};

std::map<char, size_t> countIndividual(const std::string& input) {
    std::map<char, size_t> map;
    for(int i=0; i<input.length(); i++) {
        char c = input[i];
        if(c >= 'A' && c <= 'Z') {
            c = c + 32;
        }
        if(map.count(c)) map[c] += 1;
        else map.insert({c, 1});
    }
    return map;
};

std::list<char> usedSymbols(const std::string& input) {
    std::map<char, bool> map;
    std::list<char> list;
    for(size_t i=0; i<input.length(); i++) {
        char c = input[i];
        if(c >= 'A' && c <= 'Z') {
            c = c + 32;
        }
        if(!map.count(c)) {
            map.insert({c, true});
            list.push_back(c);
        }
    }
    return list;
};

SymbolCounter::SymbolCounter(std::list<char> list) {
    for(std::list<char>::iterator it = list.begin(); it != list.end(); ++it) {
        char c = *it;
        if(c >= 'A' && c <= 'Z') {
            c = c + 32;
        }
        this->characters.insert({c, true});
    }
};

bool SymbolCounter::operator()(char c) {
    if(c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') {
        return this->characters.count(c <= 'Z' ? c + 32 : c);
    }
    else {
        return this->characters.count(c);
    }
};