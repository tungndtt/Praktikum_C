#include "strings.hpp"
#include "numerik.hpp"
#include "algorithm"
#include "math.h"
#include <iostream>

void testStrings(const std::string& str) {
    size_t count_abc = countAbc(str);
    std::cout << "number of characters = " << count_abc << std::endl;

    std::map<char, size_t> _map = countIndividual(str);
    for (std::map<char, size_t>::iterator it = _map.begin(); it != _map.end(); it++) {
        std::cout << "key: " << it->first << ", " << it->second << std::endl;
    }

    std::list<char> symbols = usedSymbols(str);
    for(std::list<char>::iterator it = symbols.begin(); it != symbols.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    SymbolCounter sc({'a', 'A', 'B', '$', '*', 'C'});
    size_t number = std::count_if(str.begin(), str.end(), sc);
    std::cout << "number of characters in given list: " << number << std::endl;
}

void testNewton() {
    auto fx = [](double x) -> double { return std::pow(x, 3) + 4 * std::pow(x, 2) - 7 * x + 12; };
    auto fderiv = [](float x) -> float { return 3 * std::pow(x, 2) + 8 * x - 7; };
    double solution = newton(fx, fderiv, 0, 2000);
    
    std::cout << "Result = " << solution << std::endl;
}

int main() {
    const std::string str = "ac&*bbbbA";
    testStrings(str);

    testNewton();
    return 0;
}