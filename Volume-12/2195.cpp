#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

class node {
public:
    int v, c, w;  // node   capacity    cost  
    node *next, *pair;
};

const int MAXN = 1010;
const int INF = 1000000000;


node *x[MAXN];
int n, m, flow, cost, dist[MAXN];
int s, t;
bool z[MAXN];

int newnode(int s, int t, int w, int c = INF) {
    node xs = {t, c, w, x[s], 0}, xt = {s, 0, -w, x[t], 0};
    x[s] = new node(xs);
    x[t] = new node(xt);
    x[s]->pair = x[t];
    x[t]->pair = x[s];
    return 0;
}

int augment(int now, int m) {
    if (now == t) return cost += dist[s]*m, flow += m, m;
    z[now] = true;
    for (node *p = x[now]; p; p = p->next)
     if (p->c && !z[p->v] && dist[p->v] + p->w == dist[now]) 
      if (int d = augment(p->v, m < p->c ? m : p->c))
       return p->c -= d, p->pair->c += d, d;
    return 0;
}

bool relabel() {
    int d = INF, w;
    for (int i = 1; i <= n; ++i) if (z[i]) 
     for (node *p = x[i]; p; p = p->next)
      if (p->c && !z[p->v]) 
       if ((w = p->w - dist[i] + dist[p->v]) < d) d = w;
    if (d == INF) return 0;
    for (int i = 1; i <= n; ++i) 
     if (z[i]) dist[i] += d;
    return 1;
}

int main() {
    while (cin >> n >> m) {
        if (n == 0) break;
        vector<pair<int, int> > M, H;
        for (int i = 0; i < n; ++i) {
            string p;
            cin >> p;
            for (int j = 0; j < m; ++j) {
                if (p[j] == 'm') M.push_back(make_pair(i, j));
                if (p[j] == 'H') H.push_back(make_pair(i, j));
            }
        }
        
        n = M.size();
        for (int i = 1; i <= n + n + 2; ++i) x[i] = NULL;
        memset(dist, 0, sizeof(dist));
        cost = 0;
        for (int i = 0; i < n; ++i)
         for (int j = 0; j < n; ++j)
          newnode(i + 1, j + n + 1, abs(M[i].first - H[j].first) + abs(M[i].second - H[j].second), 1);
        
        s = n + n + 1, t = s + 1;
        for (int i = 0; i < n; ++i) {
            newnode(s, i + 1, 0, 1);
            newnode(i + n + 1, t, 0, 1);
        }
        
        n = t;
        do 
            do 
                memset(z,0,sizeof(z));
            while (augment(s,INF));
        while (relabel());    
        cout << cost << endl;
    }
    
    return 0;
}
