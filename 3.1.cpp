#include <cstdio>
#include <iterator>

// Условие: точка [x,y] внутри фигуры, ограниченной справа линией y^2 = 3 - x, а слева прямыми y = -x и y = x.

int main() {
    double testPoints[][2] = {
        {1.0, 0.5},
        {0.5, -1.0}, 
        {0.5, 1.0}, 
        {1.5, 2.0},
        {0.0, 0.0},   
        {3.0, 0.0}   
    };
    int numTests = std::size(testPoints);

    printf("Результаты тестирования:\n");
    for (int i = 0; i < numTests; ++i) {
        double x = testPoints[i][0];
        double y = testPoints[i][1];
        int result = (x <= 3 - y * y) && (y >= -x) && (y <= x);
        printf("Точка (%g, %g) %s принадлежит области.\n", x, y, result ? "" : "не");
    }
    return 0;
}
