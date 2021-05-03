#include "rational.hpp"
#include <iostream> 

int main() {
    Rational a = Rational{1, 2};
    Rational b = Rational{1, -4};
    std::cout << "----------------------------------" << std::endl;

    // test print
    std::cout << "test print ..." << std::endl;
    a << a;
    std::cout << "----------------------------------" << std::endl;

    // test add
    std::cout << "test add ..." << std::endl;
    Rational c = Rational::simplify(a + b);
    a << c;
    std::cout << "----------------------------------" << std::endl;

    // test minus
    std::cout << "test minus ..." << std::endl;
    Rational d = Rational::simplify(a - b);
    a << d;
    std::cout << "----------------------------------" << std::endl;

    // test multiply
    std::cout << "test multiply ..." << std::endl;
    Rational e = Rational::simplify(a * b);
    a << e;
    std::cout << "----------------------------------" << std::endl;

    // test divide
    std::cout << "test devide ..." << std::endl;
    Rational f = Rational::simplify(a / b);
    a << f;
    std::cout << "----------------------------------" << std::endl;

    // test compare
    std::cout << "test compare ..." << std::endl;
    bool compare = e < c;

    std::cout << compare << std::endl;
    std::cout << "----------------------------------" << std::endl;
}