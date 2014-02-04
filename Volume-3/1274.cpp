#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 211;
const int INF = 1000000000;


int n, m;
int l[MAXN];
bool x[MAXN][MAXN], z[MAXN];


bool find(int v) {
    int k;
    for (int i = 1; i <= m; ++i)
     if (!z[i] && x[v][i]) {
         z[i] = true;
         k = l[i];
         l[i] = v;
         if (k == 0 || find(k)) return true;
         l[i] = k;
     }
    
    return false;
}


int main() {
    while (cin >> n >> m) {
        memset(x, 0, sizeof(x));
        memset(l, 0, sizeof(l));
        for (int i = 1; i <= n; ++i) {
            int a, b;
            cin >> a;
            for (int j = 0; j < a; ++j) {
                cin >> b;
                x[i][b] = true;
            }
        }
        
        for (int i = 1; i <= n; ++i) {
            memset(z, 0, sizeof(z));
            find(i);
        }
        
        int ans = 0;
        for (int i = 1; i <= m; ++i) ans += (l[i] > 0);
        
        cout << ans << endl;
    }
        
    return 0;
}
