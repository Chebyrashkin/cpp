#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> a[i][j];

    long long above_main = 0, below_main = 0, above_secondary = 0, below_secondary = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i < j) above_main += a[i][j];
            if (i > j) below_main += a[i][j];
            if (i + j < n - 1) above_secondary += a[i][j];
            if (i + j > n - 1) below_secondary += a[i][j];
        }
    }

    cout << above_main << '\n' << below_main << '\n'
         << above_secondary << '\n' << below_secondary << '\n';
    return 0;
}
