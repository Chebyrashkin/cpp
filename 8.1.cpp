#include <iostream>
using namespace std;

double sqrt_rec(double a, int tochnost) {
    if (tochnost == 0)
        return 1 + a / 2;
    else {
        double prev = sqrt_rec(a, tochnost - 1);
        return 0.5 * (prev + a / prev);
    }
}

int main() {
    double x = 2;
    // cout << sqrt(x) << endl;
    int t = 6;
    cout << sqrt_rec(x, t) << endl;
    return 0;
}
