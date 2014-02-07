#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 1100;
const int INF = 1000000000;

struct nodeP {
    int a, b, c;
};

class node {
public:
    int v, w, f, couple;
    node() { v = 0; w = 0; f = 0; }
    node(int V, int W, int F, int CC) {v = V; w = W; f = F; couple = CC;};
};

int n, m, flow, cost;
int fa[MAXN], ff[MAXN];
vector<node> x[MAXN];
nodeP y[MAXN];

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
    int times;
    cin >> times;
    while (times--) {
        int N, K;
        cin >> N >> K;
        map<int, int> C;
        for (int i = 0; i < N; ++i) {
            cin >> y[i].a >> y[i].b >> y[i].c;
            C[y[i].a] = 0;
            C[y[i].b] = 0;
        }
        
        int a = 1, b = 0;
        map<int, int>::iterator iter;
        for (iter = C.begin(); iter != C.end(); ++iter) {
            iter->second = a++;
            b = max(b, iter->first);
        }
        for (int i = 1; i <= C[b] + 1; ++i) x[i].clear();
        
        for (int i = 1; i < C[b]; ++i) newnode(i, i + 1, K, 0);
        for (int i = 0; i < N; ++i) {
            newnode(C[y[i].a], C[y[i].b], 1, -y[i].c);
        }
        newnode(C[b], C[b] + 1, K, 0);
        n = C[b] + 1;
        flow = cost = 0;
        memset(fa, 0, sizeof(fa));
        memset(ff, 0, sizeof(ff));
        Min_Cost(1, n);
        cout << -cost << endl;
    }
    return 0;
}
