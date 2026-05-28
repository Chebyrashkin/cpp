//Реализовать функцию swal для обмена значений между аргументами x и y, не
//используя при этом третьей переменной. 

#include <iostream>
using namespace std;

void swal(int &x, int &y) {
    x = x + y;
    y = x - y;
    x = x - y;
}

int main() {
    int a = 5, b = 3;
    swal(a, b);
    cout << a << ' ' << b << '\n';
    return 0;
}
