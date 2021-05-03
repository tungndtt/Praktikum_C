#include <iostream>
#include <cstdlib>
#include "rational.hpp"


// find greatest common divisor between 2 given numbers
int gcd(int A, int B) {
    int a = (int)abs(A), b = (int)abs(B);
    int small = a, big = b;
    if(small > big) {
        big = a;
        small = b;
    }

    while(small > 0) {
        int tmp = small;
        small = big%small;
        big = tmp;
    }
    
    return big;
}

// default constructor
Rational::Rational() {
    this->Z = 1;
    this->N = 2;
    std::cout << "Rational " << this->Z << "/" << this->N << " created" << std::endl;
}

// with arguements constructor
Rational::Rational(int counter, int denominator): Z(counter), N(denominator) {
    std::cout << "Rational " << this->Z << "/" << this->N << " created" << std::endl;
}

// copy constructor
Rational::Rational(const Rational& rational) {
    this->Z = rational.Z;
    this->N = rational.N;
}

// destructor
Rational::~Rational(){
    std::cout << "Rational " << this->Z << "/" << this->N << " deleted" << std::endl;
}

// overloading operator <<
std::string Rational::operator<< (const Rational& rational){
    return std::to_string(rational.Z) + "/" + std::to_string(rational.N);
}

// overloading operator +
Rational Rational::operator+ (const Rational& rational) {
    Rational result;

    if(this->N && rational.N) {
        result.Z = this->Z*rational.N + rational.Z*this->N;
        result.N = this->N*rational.N;
    }
    else std::cout << "At least one of two rationals is invalid" << std::endl;

    return result;
}

// overloading operator -
Rational Rational::operator- (const Rational& rational) {
    Rational result;

    if(this->N && rational.N) {
        result.Z = this->Z*rational.N - rational.Z*this->N;
        result.N = this->N*rational.N;
    }
    else std::cout << "At least one of two rationals is invalid" << std::endl;

    return result;
}

// overloading operator *
Rational Rational::operator* (const Rational& rational) {
    Rational result;

    if(this->N && rational.N) {
        result.Z = this->Z*rational.Z;
        result.N = this->N*rational.N;
    }
    else std::cout << "At least one of two rationals is invalid" << std::endl;

    return result;
}

// overloading operator /
Rational Rational::operator/ (const Rational& rational) {
    Rational result;

    if(this->N && rational.N && rational.Z) {
        result.Z = this->Z*rational.N;
        result.N = this->N*rational.Z;
    }
    else std::cout << "Invalid division by 0" << std::endl;

    return result;
}

// overloading operator <
bool Rational::operator< (const Rational& rational) {
    int n = rational.N, z = rational.Z;

    if(this->N && rational.N) {
        if(this->N < 0) {
            this->N *= -1;
            this->Z *= -1;
        }
        
        if(n < 0) {
            n *= -1;
            z *= -1;
        }

        return z*this->N > n*this->Z;
    }
    else {
        std::cout << "At least one of two rationals is invalid" << std::endl;
        return false;
    }
}

// simplify the given rational
Rational Rational::simplify(Rational rhs) {
    Rational simplified_result;

    if(rhs.N) {
        
        int _gcd = gcd(rhs.Z, rhs.N);
        
        simplified_result.Z = rhs.Z/_gcd;
        simplified_result.N = rhs.N/_gcd;
        
        if(simplified_result.N < 0) {
            simplified_result.Z *= -1;
            simplified_result.N *= -1;
        }
        
    }
    else std::cout << "Given rational is invalid" << std::endl;

    return simplified_result;
}