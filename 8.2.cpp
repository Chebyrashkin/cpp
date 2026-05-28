//Вычислить произведение n ≥ 2 (n четное) сомножителей

#include <iostream>
using namespace std;

double product(int n, int num = 2, int den = 1) {
    if (n == 0) return 1;
    double term = (double)num / den;
    if (n % 2 == 0)
        return term * product(n - 1, num, den + 2);
    else
        return term * product(n - 1, num + 2, den);
}

int main() {
    int n;
    cin >> n;
    cout << product(n) << endl;
    return 0;
}
