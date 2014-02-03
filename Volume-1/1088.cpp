#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

int N, M;
int f[101][101], x[101][101];

int DP(int a, int b) {
    if (f[a][b] > 0) return f[a][b];
    f[a][b] = 1;
    if (a > 0 && x[a][b] > x[a - 1][b])     f[a][b] = max(f[a][b], DP(a - 1, b) + 1);
    if (a < N - 1 && x[a][b] > x[a + 1][b]) f[a][b] = max(f[a][b], DP(a + 1, b) + 1);
    if (b > 0 && x[a][b] > x[a][b - 1])     f[a][b] = max(f[a][b], DP(a, b - 1) + 1);
    if (b < M - 1 && x[a][b] > x[a][b + 1]) f[a][b] = max(f[a][b], DP(a, b + 1) + 1);
    return f[a][b];
}


int main() {
    cin >> N >> M;
    for (int i = 0; i < N; ++i)
     for (int j = 0; j < M; ++j) cin >> x[i][j];
    
    int ans = 0;
    for (int i = 0; i < N; ++i)
     for (int j = 0; j < M; ++j) ans = max(ans, DP(i, j));
    
    cout << ans << endl;
    
    return 0;
}
