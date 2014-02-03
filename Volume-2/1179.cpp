#include <vector>
#include <string>
#include <iostream>
using namespace std;

const int MAXN = 101;
const int INF = 1000000000;

int x[MAXN];
bool y[MAXN];
int f[MAXN][MAXN], g[MAXN][MAXN];
bool z[MAXN][MAXN];

int dp(int a, int b) {
    if (z[a][b]) return 0;
    if (a == b) {
        f[a][b] = g[a][b] = x[a];
        z[a][b] = true;
        return 0;
    }
    if (a + 1 == b) {
        f[a][b] = g[a][b] = (y[b] ? x[a] * x[b] : x[a] + x[b]);
        return 0;
    }
    
    z[a][b] = true;
    f[a][b] = -INF;
    g[a][b] = INF;
    for (int k = a; k < b; ++k) {
        dp(a, k);
        dp(k + 1, b);
        if (!y[k + 1]) {
            // add is so easy
            f[a][b] = max(f[a][b], f[a][k] + f[k + 1][b]);
            g[a][b] = min(g[a][b], g[a][k] + g[k + 1][b]);
        } else {
            // multi is hard
            f[a][b] = max(f[a][b], f[a][k] * f[k + 1][b]);
            f[a][b] = max(f[a][b], f[a][k] * g[k + 1][b]);
            f[a][b] = max(f[a][b], g[a][k] * f[k + 1][b]);
            f[a][b] = max(f[a][b], g[a][k] * g[k + 1][b]);
            g[a][b] = min(g[a][b], f[a][k] * f[k + 1][b]);
            g[a][b] = min(g[a][b], f[a][k] * g[k + 1][b]);
            g[a][b] = min(g[a][b], g[a][k] * f[k + 1][b]);
            g[a][b] = min(g[a][b], g[a][k] * g[k + 1][b]);
        }
    }
    return 0;
}


int main() {
    int N;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        string p;
        int a;
        cin >> p >> a;
        x[i] = x[N + i] = a;
        y[i] = y[N + i] = (p == "x");
    }
    
    for (int i = 0; i < N; ++i) dp(i, N + i - 1);
    
    int ans = -INF;
    for (int i = 0; i < N; ++i) ans = max(ans, f[i][N + i - 1]);
    cout << ans << endl;
    vector<int> ansL;
    for (int i = 0; i < N; ++i) if (ans == f[i][N + i - 1]) ansL.push_back(i + 1);
    for (int i = 0; i < ansL.size() - 1; ++i) cout << ansL[i] << " ";
    cout << ansL[ansL.size() - 1] << endl;
    
    return 0;
}
