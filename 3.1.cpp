#include <cstdio>

// Условие: точка [x,y] внутри фигуры, ограниченной справа линией y^2 = 3-x, а слева прямыми y = -x и y = x.

int main() {
    double x, y;
    printf("Введите координаты x y: ");
    scanf("%lf %lf", &x, &y);
    int result = (x <= 3 - y * y) && (y >= -x) && (y <= x);
    printf("Точка (%g, %g) %s принадлежит области.\n", x, y, result ? "" : "не");
    return 0;
}
