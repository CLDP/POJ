#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

int N, K, M;
int f[35][35][35][2];
bool z[35][35][35][2];

int DP(int a, int b, int c, bool d) {
    if (a == N - 1) {
        if (c == 0 && b == 0) return 1;
        return 0;
    }
    
    if (z[a][b][c][d]) return f[a][b][c][d];
    z[a][b][c][d] = true;
    if (b > 0) return f[a][b][c][d] = DP(a + 1, b - 1, c, d);
    if (b == 0) {
        for (int i = 1; i <= M; ++i) f[a][b][c][d] += DP(a + 1, i - 1, c - 1, !d);
    }
    return f[a][b][c][d];
}

int getans(int a, int b, int c, bool d, string &p) {
    if (a == p.size()) return 0;
    if (p[a] == '1') {
        int ans = 0;
        if (d == 0) {
            for (int i = b; i < M; ++i) ans += f[a - b][i][c][d];
            return ans + getans(a + 1, 1, c - 1, !d, p);
        } else {
            for (int i = 0; i < M; ++i) ans += f[a][i][c - 1][!d];
            return ans + getans(a + 1, b + 1, c, d, p);
        }
    } else {
        if (d == 0) 
            return getans(a + 1, b + 1, c, d, p);
        else
            return getans(a + 1, 1, c - 1, !d, p);
    }
}

int main() {
    int ans = 0;
    cin >> N >> K >> M;
    for (int i = 1; i <= M; ++i) {
        ans += DP(0, i - 1, K - 1, 1);
    }
    cout << ans << endl;
    
    int T;
    cin >> T;
    for (int i = 0; i < T; ++i) {
        string p;
        cin >> p;
        cout << getans(1, 1, K - 1, 1, p) << endl;
    }
    
    return 0;
}
