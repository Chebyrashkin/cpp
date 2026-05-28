//Реализовать обобщенную функцию печати значения функции от аргумента

#include <iostream>
#include <cmath>
using namespace std;

double f1(double x) { return sin(x) / x; }
double f2(double y) { return y*y + 2*pow(y, 1.5); }
double f3(double z) { return (z+2)*(z+1)*z; }

void print(double x, double (*func)(double)) {
    cout << func(x) << '\n';
}

int main() {
    double x = 0.6, y = 0.3, z = 0.1;
    double R = f1(x) + f2(y) * f3(f2(z));
    cout.precision(6);
    cout << "R = " << R << '\n';
    cout << "f1(0.6) = "; print(0.6, f1);
    cout << "f2(0.3) = "; print(0.3, f2);
    return 0;
}
