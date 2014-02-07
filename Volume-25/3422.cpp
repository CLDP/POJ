#include <iostream>
#include <vector>
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 6000;
const int INF = 1000000000;

class node {
public:
    int v, w, f, couple;
    node() { v = 0; w = 0; f = 0; }
    node(int V, int W, int F, int CC) {v = V; w = W; f = F; couple = CC;};
};

int n, m, flow, cost;
int fa[MAXN], ff[MAXN];
vector<node> x[MAXN];


// s, t, capacity, cost
int newnode(int a, int b, int c, int d) {
    node p(b, d, c, x[b].size());
    node q(a, -d, 0, x[a].size());
    x[a].push_back(p);
    x[b].push_back(q);
    return 0;
}

int SPFA(int s, int t) {
    vector<int> d(n + 1, INF);
    vector<bool> z(n + 1, false);
    d[s] = 0;
    queue<int> que;
    que.push(s);
    z[s] = true;
    while (!que.empty()) {
        int i = que.front();
        que.pop();
        for (vector<node>::iterator p = x[i].begin(); p != x[i].end(); ++p) {
            if (p->f > 0 && d[p->v] > d[i] + p->w) {
                d[p->v] = d[i] + p->w;
                fa[p->v] = i;
                ff[p->v] = p - x[i].begin();
                if (!z[p->v]) {
                    z[p->v] = true;
                    que.push(p->v);
                }
            }
        }
        z[i] = false;
    }
    return d[t];
}

int Min_Cost(int s, int t) {
    while (SPFA(s,t) < INF) {
        int i = t, now = INF;
        while (i != s) {
            node &p = x[fa[i]][ff[i]];
            i = fa[i];
            if (p.f < now) now = p.f;
        }
        flow += now;
        
        i = t;
        while (i != s) {
            x[fa[i]][ff[i]].f -= now;
            cost += now * x[fa[i]][ff[i]].w;
            x[i][x[fa[i]][ff[i]].couple].f += now;
            i = fa[i];
        }
    }
    return 0;
}


int main() {
    int N, M;
    cin >> N >> M;
    if (M == 0) {
        cout << 0 << endl;
        return 0;
    }
    int B = N * N;
    for (int i = 0; i < N; ++i)
     for (int j = 0; j < N; ++j) {
         int a;
         cin >> a;
         if (j < N - 1) newnode(B + i * N + j + 1, i * N + j + 2, INF, 0);
         if (i < N - 1) newnode(B + i * N + j + 1, (i + 1) * N + j + 1, INF, 0);
         newnode(i * N + j + 1, B + i * N + j + 1, 1, -a);
         newnode(i * N + j + 1, B + i * N + j + 1, M - 1, 0);
     }
    
    n = N * N * 2;
    
    Min_Cost(1, n);
    cout << -cost << endl;
    return 0;
}
