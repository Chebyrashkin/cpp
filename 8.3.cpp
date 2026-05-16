#include <iostream>
using namespace std;

void reverse_print(int arr[], int n) {
    if (n == 0) return;
    cout << arr[n - 1] << ' ';
    reverse_print(arr, n - 1);
}

int main() {
    int a[] = {1, 2, 3, 4, 5};
    int n = size(a);
    reverse_print(a, n);
    return 0;
}
