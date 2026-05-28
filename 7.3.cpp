//Реализуйте перегрузку функций max и min для массива из k вещественных
//чисел. С помощью программы найдите произведение минимумов двух
//массивов различной длины и среднее геометрическое их максимумов

#include <iostream>
#include <cmath>
#include <iterator>
using namespace std;

double max(double arr[], int k) {
    double m = arr[0];
    for (int i = 1; i < k; ++i)
        if (arr[i] > m) m = arr[i];
    return m;
}

double min(double arr[], int k) {
    double m = arr[0];
    for (int i = 1; i < k; ++i)
        if (arr[i] < m) m = arr[i];
    return m;
}

int main() {
    double a[] = {1.5, -2.3, 4.2, 0.1};
    double b[] = {3.1, -1.8, 2.7};

    double min_a = min(a, size(a));
    double min_b = min(b, size(b));
    double prod_min = min_a * min_b;

    double max_a = max(a, size(a));
    double max_b = max(b, size(b));
    double geom_max = sqrt(max_a * max_b);

    cout << prod_min << '\n' << geom_max << '\n';
    return 0;
}
