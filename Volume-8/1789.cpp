#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 2011;
const int INF = 1000000000;

int x[MAXN][MAXN], d[MAXN];
bool z[MAXN];
string y[MAXN];


int main() {
    int N;
    while (cin >> N) {
        if (N == 0) break;
        for (int i = 1; i <= N; ++i) cin >> y[i];
        for (int i = 1; i <= N; ++i)
         for (int j = i + 1; j <= N; ++j) {
             int diff = 0;
             for (int k = 0; k < 7; ++k) diff += y[i][k] != y[j][k];
             x[i][j] = x[j][i] = diff;
         }
         
        for (int i = 1; i <= N; ++i) {
            d[i] = INF;
            z[i] = false;
        }
        
        d[1] = 0;
        int ans = 0;
        for (int i = 0; i < N; ++i) {
            int a = -1, b = INF;
            for (int j = 1; j <= N; ++j) {
                if (z[j] || d[j] >= b) continue;
                a = j;
                b = d[j];
            }
            z[a] = true;
            ans += b;
            for (int j = 1; j <= N; ++j) d[j] = min(d[j], x[a][j]);
        }
        
        cout << "The highest possible quality is 1/" << ans << "." << endl;
    }
    
    return 0;
}
