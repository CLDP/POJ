#include <cstring>
#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 210;

int x[MAXN];
int f[MAXN][MAXN][MAXN];

int dp(int a, int b, int c) {
    if (a > b) return 0;
    if (f[a][b][c] != -1) return f[a][b][c];
    f[a][b][c] = dp(a, b - 1, 0) + (c + 1) * (c + 1);
    for (int i = a; i < b; ++i) {
        if (x[i] != x[b]) continue;
        f[a][b][c] = max(f[a][b][c], dp(a, i, c + 1) + dp(i + 1, b - 1, 0));
    }
    return f[a][b][c];
}


int main() {
    int times;
    cin >> times;
    for (int tt = 1; tt <= times; ++tt) {
        int N;
        cin >> N;
        for (int i = 0; i < N; ++i) cin >> x[i];
        memset(f, -1, sizeof(f));
        cout << "Case " << tt << ": " << dp(0, N - 1, 0) << endl;
    }
    return 0;
}
