#include <cstdio>
#include <cstring>

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
    int a, b, c;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i) {
        scanf("%d%d%d", &a, &b, &c);
        newnode(a, b, c, 1);
        newnode(b, a, c, 1);
    }
    s = 1, t = n + 1;
    n = t;
    newnode(n - 1, t, 0, 2);
    do 
        do 
            memset(z,0,sizeof(z));
        while (augment(s,INF));
    while (relabel());    
    printf("%d\n", cost);
    return 0;
}
