#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 101;
const int MAXM = 100010;
const int INF = 1000000000;

int v[MAXN], w[MAXN], x[MAXM];
bool f[MAXM];



int main() {
    int N, M;
    while (cin >> N >> M) {
        if (N == 0) break;
        for (int i = 0; i < N; ++i) cin >> v[i];
        for (int i = 0; i < N; ++i) cin >> w[i];
        
        memset(f, 0, sizeof(f));
        f[0] = true;
        for (int i = 0; i < N; ++i) {
            memset(x, 0, sizeof(x));
            for (int j = v[i]; j <= M; ++j) {
                if (f[j]) continue;
                if (f[j - v[i]] && x[j - v[i]] < w[i]) {
                    f[j] = true;
                    x[j] = x[j - v[i]] + 1;
                }
            }
        }
        int ans = 0;
        for (int i = 1; i <= M; ++i) ans += f[i];
        cout << ans << endl;
    }
    
    return 0;
}
