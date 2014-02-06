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

const int MAXL = 201;
const int MAXN = 410;
const int INF = 1000000000;


node *x[MAXN];
int n, m, flow, cost, dist[MAXN];
int s, t;
bool z[MAXN];
int NK[MAXL][MAXL], MK[MAXL][MAXL], KNM[MAXL][MAXL][MAXL];


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
    int N, M, K;
    while (cin >> N >> M >> K) {
        if (N == 0) break;
        
        for (int i = 1; i <= N; ++i)
         for (int j = 1; j <= K; ++j) scanf("%d", &NK[i][j]);
        
        for (int i = 1; i <= M; ++i)
         for (int j = 1; j <= K; ++j) scanf("%d", &MK[i][j]);
         
        for (int k = 1; k <= K; ++k)
         for (int i = 1; i <= N; ++i)
          for (int j = 1; j <= M; ++j) scanf("%d", &KNM[k][i][j]);
        
        int total_cost = 0;
        for (int k = 1; k <= K; ++k) {
            int total = 0;
            n = N + M + 2;
            s = n - 1, t = n;
            for (int i = 1; i <= n; ++i) x[i] = NULL;
            for (int i = 1; i <= N; ++i) total += NK[i][k];
            
            for (int i = 1; i <= N; ++i) newnode(M + i, t, 0, NK[i][k]);
            for (int i = 1; i <= M; ++i) newnode(s, i, 0, MK[i][k]);
            for (int i = 1; i <= M; ++i)
             for (int j = 1; j <= N; ++j) newnode(i, M + j, KNM[k][j][i], INF);
            
            memset(dist, 0, sizeof(dist));
            flow = cost = 0;
            do 
                do 
                    memset(z,0,sizeof(z));
                while (augment(s,INF));
            while (relabel());
            if (flow != total || total_cost == -1) total_cost = -1; else total_cost += cost;
        }
        
        cout << total_cost << endl;
    }
    
    return 0;
}
