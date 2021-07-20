#pragma once
#include <string>
#include <map>
#include <list>

size_t countAbc(const std::string& input);

std::map<char, size_t> countIndividual(const std::string& input);

std::list<char> usedSymbols(const std::string& input);

class SymbolCounter {
public:
    SymbolCounter(std::list<char> list);

    bool operator()(char c);

private:
    std::map<char, bool> characters;
};