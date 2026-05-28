//Дано натуральное число N. Выведите слово YES, если число N является
//точной степенью двойки, или слово NO в противном случае. Операцией
//возведения в степень пользоваться нельзя!


#include <iostream>
using namespace std;

bool is_power_of_two(int n) {
    if (n <= 0) return false;
    if (n == 1) return true;
    if (n % 2 != 0) return false;
    return is_power_of_two(n / 2);
}

int main() {
    int N;
    cin >> N;
    cout << (is_power_of_two(N) ? "YES" : "NO") << endl;
    return 0;
}
