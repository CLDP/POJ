#include <cstdio>
#include <vector>
#include <cmath>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 110;
const int INF = 1000000000;
const double INFD = 1e10;
const double EPS = 1e-5;

struct node {
    int v, k;
    double f;
    
    node(int _v, double _f) : v(_v), f(_f) {}
};

vector<node> x[MAXN];
vector<int> y[MAXN];


// n must be total number of vertices
double max_flow(int s, int t, int n) {
    vector<double> ff(n + 1, 0);
    vector<int> fa(n + 1, 0);
    vector<int> h(n + 1, 0);
    vector<int> hh(n + 1, 0);
    vector<int> fi(n + 1, 0);
    
    int i = 0;
    double ans = 0, now = INFD;
    hh[0] = n;
    
    i = s;
    
    while (h[s] < n) {
        ff[i] = now;
        bool flag = false;
        vector<node>::iterator p = x[i].begin();
        while (p != x[i].end()) {
            if (p->f > 0 && h[p->v] + 1 == h[i]) {
                flag = true;
                if (p->f < now) now = p->f;
                fa[p->v] = i;
                fi[p->v] = p - x[i].begin();
                i = p->v;
                if (i == t) {
                    ans += now;
                    while (i != s) {
                        int tmp = i;
                        i = fa[i];
                        p = x[i].begin() + fi[tmp];
                        p->f -=now;
                        x[tmp][p->k].f += now;
                    }
                    now = INFD;
                }
                break;
            }
            ++p;
        }
        if (flag) continue;
        
        int min = n-1;
        p = x[i].begin();
        while (p != x[i].end()) {
            if (p->f > 0 && h[p->v] < min) min = h[p->v];
            ++p;
        }
        
        --hh[h[i]];
        if (hh[h[i]] == 0) break;
        h[i] = min + 1;
        ++hh[h[i]];
        if (i != s) {
            i = fa[i];
            now = ff[i];
        }
    }
    
    return ans;
}

int add_edge(int s, int t, double w1, double w2) {
    x[s].push_back(node(t, w1));
    x[t].push_back(node(s, w2));
    int a = x[s].size() - 1, b = x[t].size() - 1;
    x[s][a].k = b;
    x[t][b].k = a;
    return 0;
}


int make_edge(int s, int t, int N, int M, double mid) {
    for (int i = 1; i <= t; ++i) x[i].clear();
    
    for (int i = 1; i <= N; ++i) {
        add_edge(s, i, M, 0);
        add_edge(i, t, M + 2 * mid - y[i].size(), 0);
    }
    for (int i = 1; i <= N; ++i)
     for (int j = 0; j < y[i].size(); ++j) 
      if (i < y[i][j]) add_edge(i, y[i][j], 1, 1);
      
    return 0;
}


int dfs(int a, vector<bool> &z) {
    z[a] = true;
    for (int i = 0; i < x[a].size(); ++i)
     if (!z[x[a][i].v] && x[a][i].f > 0) {
         dfs(x[a][i].v, z);
     }
    return 0;
}


int main() {
    int N, M;
    cin >> N >> M;
    if (M == 0) {
        cout << 1 << endl << 1 << endl;
        return 0;
    }
    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        y[a].push_back(b);
        y[b].push_back(a);
    }
    
    double L = 0, R = M;
    int s = N + 1, t = s + 1;
    while (R - L > 1.0 / N / N) {
        double mid = (L + R) / 2;
        make_edge(s, t, N, M, mid);
        double ans = max_flow(s, t, t);
        if ((M * N - ans) > 2 * EPS) L = mid; else R = mid;
    }
    
    make_edge(s, t, N, M, L);
    max_flow(s, t, t);
    
    vector<bool> z(t + 1, false);
    dfs(s, z);
    
    vector<int> ansT;
    for (int i = 1; i <= N; ++i) 
     if (z[i]) ansT.push_back(i);
    
    cout << ansT.size() << endl;
    for (int i = 0; i < ansT.size(); ++i) cout << ansT[i] << endl;
    
    return 0;
}
