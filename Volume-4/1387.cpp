#include <cstdio>
#include <vector>
#include <cmath>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 210;

int x[MAXN][MAXN];
long long s[MAXN][MAXN], ss[MAXN][MAXN], qx[MAXN], qy[MAXN];

int cmp(const double &A, const double &B) {
    if (fabs(A - B) < 1e-8) return 0;
    return A > B ? 1 : -1;
}


int main() {
    int N, M, R, C;
    while (true) {
        scanf("%d%d%d%d", &N, &M, &R, &C);
        if (N == 0) break;
        for (int i = 1; i <= N; ++i) 
         for (int j = 1; j <= M; ++j) {
             scanf("%d", &x[i][j]);
             s[i][j] = s[i - 1][j] + x[i][j];
             ss[i][j] = ss[i][j - 1] + s[i][j];
         }
        
        double ans = 0;
        int x1, y1, x2, y2;
        for (int i1 = 1; i1 <= N; ++i1)
         for (int i2 = i1 + R - 1; i2 <= N; ++i2) {
             int l = 0, r = 1;
             qx[l] = 0, qy[l] = 0;
             for (int j = C; j <= M; ++j) {
                 int tx = j, ty = ss[i2][j] - ss[i1 - 1][j];
                 while (l + 1 < r && (ty - qy[l + 1]) * (tx - qx[l]) >= (ty - qy[l]) * (tx - qx[l + 1])) ++l;
                 double temp = 1.0 * (ty - qy[l]) / (tx - qx[l]) / (i2 - i1 + 1);
                 if (cmp(temp, ans) == 1) {
                     ans = temp;
                     x1 = i1, x2 = i2, y1 = qx[l] + 1, y2 = tx;
                 } else
                 if (cmp(temp, ans) == 0) {
                     if (i1 < x1 || (i1 == x1 && qx[l] + 1 < y1) 
                                 || (i1 == x2 && qx[l] + 1 == y2 && i2 < x2)
                                 || (i1 == x2 && qx[l] + 1 == y2 && i2 == x2 && tx < y2)) {
                         x1 = i1, x2 = i2, y1 = qx[l] + 1, y2 = tx;
                     }
                 }
                 tx = j - C + 1, ty = ss[i2][tx] - ss[i1 - 1][tx];
                 while (l + 1 < r && (ty - qy[r - 1]) * (qx[r - 1] - qx[r - 2]) 
                                  <= (qy[r - 1] - qy[r - 2]) * (tx - qx[r - 1])) --r;
                 qx[r] = tx, qy[r] = ty;
                 ++r;
             }
         }
         
        cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
    }
    cout << "*" << endl;
    
    return 0;
}
