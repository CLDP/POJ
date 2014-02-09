#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1100;
const int INF = 1000000000;

int n, m;
int l[MAXN], x[MAXN][MAXN];
bool z[MAXN];
pair<int, int> y[MAXN];


bool find(int v) {
    int k;
    for (int i = 1; i <= m; ++i) 
     if (!z[i] && x[v][i]) {
         z[i] = 1;
         k = l[i];
         l[i] = v;
         if (!k || find(k)) return 1;
         l[i] = k;
     }
    return 0;
}


int main() {
    int times;
    cin >> times;
    while (times--) {
        cin >> n >> m;
        memset(x, 0, sizeof(x));
        memset(l, 0, sizeof(l));
        
        for (int i = 1; i <= m; ++i) {
            cin >> y[i].first >> y[i].second;
            x[y[i].first][i] = x[y[i].second][i] = 1;
        }
        
        for (int i = 1; i <= n; ++i) {
            memset(z, 0, sizeof(z));
            find(i);
        } 
        int ans = 0;
        for (int i = 1; i <= m; ++i) ans += (l[i] > 0);
        if (ans < n) {
            cout << "NO" << endl;
            continue;
        }
        
        for (int i = 1; i <= m; ++i) { 
            if (l[i] > 0) cout << l[i]; else cout << y[i].first;
            if (i == m) cout << endl; else cout << " ";
        }
    }
    
    return 0;
}
