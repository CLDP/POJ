#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 101;
const int INF = 1000000000;

int x[MAXN][MAXN];
int d[MAXN];
bool z[MAXN];

int main() {
    int N;
    while (cin >> N) {
        for (int i = 0; i < N; ++i)
         for (int j = 0; j < N; ++j) cin >> x[i][j];
        
        for (int i = 0; i < N; ++i) {
            d[i] = INF;
            z[i] = false;
        }
        int ans = 0;
        d[0] = 0;
        for (int i = 0; i < N; ++i) {
            int a = -1, b = INF;
            for (int j = 0; j < N; ++j) {
                if (z[j] || d[j] >= b) continue;
                a = j;
                b = d[j];
            }
            
            if (a == -1) break;
            z[a] = true;
            ans += d[a];
            for (int j = 0; j < N; ++j)
             if (x[a][j] < d[j]) d[j] = x[a][j];
        }
        cout << ans << endl;
    }
    return 0;
}
