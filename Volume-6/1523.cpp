#include <cstdio>
#include <vector>
#include <cmath>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1010;

int dfn[MAXN], low[MAXN];
bool y[MAXN], z[MAXN], cz[MAXN];
vector<int> x[MAXN];


int dfs(int a, int f, int &time) {
    dfn[a] = low[a] = time;
    int s = 0;
    bool flag = false;
    for (int i = 0; i < x[a].size(); ++i) {
        if (x[a][i] == f) continue;
        if (dfn[x[a][i]] == 0) {
            dfs(x[a][i], a, ++time);
            ++s;
            low[a] = min(low[a], low[x[a][i]]);
            if (low[x[a][i]] >= dfn[a]) flag = true;
        } else {
            low[a] = min(low[a], dfn[x[a][i]]);
        }
    }
    if ((f != -1 && flag) || (f == -1 && s > 1)) z[a] = true;
    return 0;
}


int dfs(int a) {
    cz[a] = true;
    for (int i = 0; i < x[a].size(); ++i) {
        if (cz[x[a][i]]) continue;
        dfs(x[a][i]);
    }
    return 0;
}


int main() {
    int times = 0;
    while (true) {
        int a, b;
        cin >> a;
        if (a == 0) break;
        for (int i = 1; i <= 1000; ++i) x[i].clear();
        
        memset(y, 0, sizeof(y));
        memset(z, 0, sizeof(z));
        memset(dfn, 0, sizeof(dfn));
        memset(low, 0, sizeof(low));
        
        int N = 1;
        while (a != 0) {
            cin >> b;
            x[a].push_back(b);
            x[b].push_back(a);
            N = max(N, a);
            N = max(N, b);
            y[a] = y[b] = true;
            cin >> a;
        }
        
        dfs(1, -1, a = 1);
        
        int ans = 0;
        for (int i = 1; i <= N; ++i) ans += z[i];
        
        cout << "Network #" << ++times << endl;
        if (ans == 0) {
            cout << "  No SPF nodes" << endl;
        } else {
            for (int i = 1; i <= N; ++i) {
                if (!y[i] || !z[i]) continue;
                memset(cz, 0, sizeof(cz));
                cz[i] = true;
                int ans2 = 0;
                for (int j = 1; j <= N; ++j) {
                    if (!y[j] || cz[j]) continue;
                    dfs(j);
                    ++ans2;
                }
                cout << "  SPF node " << i << " leaves " << ans2 << " subnets" << endl;
            }
        }
        cout << endl;
        
    }
    return 0;
}
