#include <iostream>
using namespace std;

double power(double x, int a) {
    if (a == 0) return 1;
    if (a % 2 == 0) {
        double t = power(x, a / 2);
        return t * t;
    } else {
        return x * power(x, a - 1);
    }
}

int main() {
    double x;
    int a;
    cin >> x >> a;
    cout << power(x, a) << endl;
    return 0;
}
