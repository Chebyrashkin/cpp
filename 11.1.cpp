#include "Fraction.h"
#include <cstdlib>   
using namespace std;

Fraction::Fraction(int num, int den) : numerator(num), denominator(den) {
    if (denominator == 0) denominator = 1;
    reduce();
}

int gcd(int a, int b) {
    a = abs(a); b = abs(b);
    while (b != 0) { int t = b; b = a % b; a = t; }
    return a;
}

void Fraction::reduce() {
    if (denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }
    int g = gcd(numerator, denominator);
    numerator /= g;
    denominator /= g;
}

Fraction Fraction::operator+(const Fraction& other) const {
    int new_num = numerator * other.denominator + other.numerator * denominator;
    int new_den = denominator * other.denominator;
    return Fraction(new_num, new_den);
}

Fraction Fraction::operator-(const Fraction& other) const {
    int new_num = numerator * other.denominator - other.numerator * denominator;
    int new_den = denominator * other.denominator;
    return Fraction(new_num, new_den);
}

Fraction Fraction::operator*(const Fraction& other) const {
    return Fraction(numerator * other.numerator, denominator * other.denominator);
}

Fraction Fraction::operator/(const Fraction& other) const {
    return Fraction(numerator * other.denominator, denominator * other.numerator);
}

void Fraction::print() const {
    cout << numerator << "/" << denominator;
}


int main() {
    Fraction a(3, 4), b(1, 2);
    Fraction c = a + b;
    c.print(); cout << endl;   // 5/4
    Fraction d = a * b;
    d.print();                 // 3/8
    return 0;
}
