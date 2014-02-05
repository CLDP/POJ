#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int T[1026][1026];

int add(int x, int y, int n, int val) {
    for (int i = x; i <= n; i += i & -i) 
     for (int j = y; j <= n; j += j & -j) T[i][j] += val;
    return 0;
}

int sum(int x, int y) {
    int res = 0;
    for (int i = x; i > 0; i -= i & -i)
     for (int j = y; j > 0; j -= j & -j) res += T[i][j];
    return res;
}


int main() {
    int P, N;
    while (cin >> P) {
        if (P == 3) break;
        if (P == 0) {
            cin >> N;
            memset(T, 0, sizeof(T));
        }
        if (P == 1) {
            int x, y, t;
            cin >> x >> y >> t;
            add(x + 1, y + 1, N, t);
        }
        if (P == 2) {
            int x1, x2, y1, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            cout << sum(x2 + 1, y2 + 1) + sum(x1, y1) - sum(x1, y2 + 1) - sum(x2 + 1, y1) << endl;
        }
    }
    return 0;
}
