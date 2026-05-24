#include <cstdio>
#include <cmath>

int main() {
    // Задание а) Арифметическое выражение sqrt(7.002 * sqrt(0.1) - 1) - cos(π/6) * ln(3.4)
    printf("Задание а:\n");
    double a = sqrt(7.002 * sqrt(0.1) - 1) - cos(M_PI / 6) * log(3.4);
    printf("Результат: %.6f\n\n", a);

    // Задание б) Вычисление при введённом x
    printf("Задание б:\n");
    double x;
    printf("Введите значение x (в радианах): ");
    scanf("%lf", &x);   
    double b = (2 * x - 1) * exp(x) + log(fabs(tan(x)));
    printf("Результат: %.6f\n\n", b);

    // Задание в) Пять членов последовательности A_{j+1} = j*A_j + (j+1)*A_{j-1}
    printf("Задание в:\n");
    double A0 = 1.0;
    double A1 = 2.0;
    double A2 = 1 * A1 + (1 + 1) * A0;   
    double A3 = 2 * A2 + (2 + 1) * A1;   
    double A4 = 3 * A3 + (3 + 1) * A2;   
    
    printf("Пять первых членов последовательности:\n");
    printf("A0 = %10.0f\n", A0);
    printf("A1 = %10.0f\n", A1);
    printf("A2 = %10.0f\n", A2);
    printf("A3 = %10.0f\n", A3);
    printf("A4 = %10.0f\n", A4);

    return 0;
}
