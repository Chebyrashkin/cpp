#ifndef FRACTION_H
#define FRACTION_H
#include <iostream>

class Fraction {
private:
    int numerator;
    int denominator;
    void reduce();          
public:
    Fraction(int num = 0, int den = 1);
    ~Fraction() {}            

    Fraction operator+(const Fraction& other) const;
    Fraction operator-(const Fraction& other) const;
    Fraction operator*(const Fraction& other) const;
    Fraction operator/(const Fraction& other) const;

    void print() const;
};
#endif
