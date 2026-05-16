#include <iostream>
using namespace std;

int sum_of_digits(int n) {
    if (n < 10) return n;
    return n % 10 + sum_of_digits(n / 10);
}

int main() {
    int N;
    cin >> N;
    cout << sum_of_digits(N) << endl;
    return 0;
}
