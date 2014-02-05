#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 30;
const int MAXM = 10010;

int n, path[MAXN][MAXN][MAXN];
double f[MAXN][MAXN][MAXN];


int printpath(int i, int j, int p) {
    if (p == 0) {
        cout << " " << i + 1;
    } else {
        printpath(i, path[i][j][p], p - 1);
        cout << " " << j + 1;
    }
    return 0;
}

int Floyd() {
    for (int p = 1; p < n; ++p) {
        for (int k = 0; k < n; ++k)
         for (int i = 0; i < n; ++i)
          for (int j = 0; j < n; ++j)
           if (f[i][k][p] * f[k][j][1] > f[i][j][p + 1] + 1e-9) {
               f[i][j][p + 1] = f[i][k][p] * f[k][j][1];
               path[i][j][p + 1] = k;
           }
           
        for (int i = 0; i < n; ++i)
         if (f[i][i][p+1] > 1.01) {
             printpath(i, i, p+1);
             cout << endl;
             return 0;
         }
    }
    cout << "no arbitrage sequence exists" << endl;
    return 0;
}


int main() {
    while (cin >> n) {
        memset(f, 0, sizeof(f));
        for (int i = 0; i < n; ++i)
         for (int j = 0; j < n; ++j)
          if (i != j) {
              cin >> f[i][j][1];
              path[i][j][1] = i;
          }
        Floyd();
    }
    return 0;
}
