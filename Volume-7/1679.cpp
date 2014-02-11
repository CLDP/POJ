#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 111;
const int MAXM = 20010;
const int INF = 1000000000;

struct line {
    int a, b, c;
    bool operator < (line const &B) const {
        return c < B.c;
    }
};


vector<pair<int, int> > x[MAXN];
line y[MAXM];
int d[MAXN], f[MAXN], z[MAXN][MAXN];


int find(int a) {
    if (a != f[a]) f[a] = find(f[a]);
    return f[a];
}

int Union(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return 0;
    if (d[a] > d[b]) f[b] = f[a]; else f[a] = f[b];
    d[a] += d[b];
    d[b] = d[a];
    return 0;
}

int dfs(int root, int a, int d) {
    z[root][a] = d;
    for (int i = 0; i < x[a].size(); ++i) {
        if (x[a][i].first == root || z[root][x[a][i].first] > 0) continue;
        dfs(root, x[a][i].first, max(d, x[a][i].second));
    }
    return 0;
}


int main() {
    int times;
    cin >> times;
    while (times--) {
        int N, M, a, b;
        scanf("%d%d", &N, &M);
        for (int i = 0; i < M; ++i) scanf("%d%d%d", &y[i].a, &y[i].b, &y[i].c);
        sort(y, y + M);
        for (int i = 1; i <= N; ++i) {
            d[i] = 1;
            f[i] = i;
            x[i].clear();
        }
        
        int ans = 0;
        vector<line> YY;
        for (int i = 0; i < M; ++i) {
            int a = y[i].a, b = y[i].b, c = y[i].c;
            a = find(a), b = find(b);
            if (a == b) {
                YY.push_back(y[i]);
                continue;
            }
            a = y[i].a, b = y[i].b;
            x[a].push_back(make_pair(b, c));
            x[b].push_back(make_pair(a, c));
            Union(a, b);
            ans += y[i].c;
        }
        
        memset(z, 0, sizeof(z));
        for (int i = 1; i <= N; ++i) dfs(i, i, 0);
        
        bool flag = false;
        for (int i = 0; i < YY.size(); ++i) {
            if (z[YY[i].a][YY[i].b] == YY[i].c) {
                flag = true;
                break;
            }
        }
        
        if (flag) 
            cout << "Not Unique!" << endl;
        else
            cout << ans << endl;
    }
    
    return 0;
}
