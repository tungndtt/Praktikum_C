#pragma once
#include <iostream>

class Rational {
public:
    int Z, N;
    Rational();
    Rational(int counter, int denominator);
    Rational(const Rational& rational);
    ~Rational();

    std::string operator<< (const Rational& rational);
    Rational operator+ (const Rational& rational);
    Rational operator- (const Rational& rational);
    Rational operator* (const Rational& rational);
    Rational operator/ (const Rational& rational);
    bool operator< (const Rational& rational);

    static Rational simplify(Rational rhs);
};