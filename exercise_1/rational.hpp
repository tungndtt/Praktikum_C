#pragma once

class Rational {
public:
    int Z, N;
    Rational();
    Rational(int counter, int denominator);
    Rational(const Rational& r);
    ~Rational();

    void operator<< (const Rational& rational);
    Rational operator+ (const Rational& rational);
    Rational operator- (const Rational& rational);
    Rational operator* (const Rational& rational);
    Rational operator/ (const Rational& rational);
    bool operator< (const Rational& rational);

    static Rational simplify(Rational rhs);
};