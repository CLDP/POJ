#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 201;
const int MAXM = 20010;
const int INF = 1000000000;

struct line {
    int a, b, c;
    bool operator < (line const &B) const {
        return c < B.c;
    }
};


line y[MAXM];
int d[MAXN], f[MAXN];
int x[MAXN][MAXN];


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



int main() {
    int N, M, a, b;
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i)
     for (int j = 1; j <= N; ++j) scanf("%d", &x[i][j]);
    
    for (int i = 1; i <= N; ++i) {
        d[i] = 1;
        f[i] = i;
    }
    
    scanf("%d", &M);
    for (int i = 0; i < M; ++i) {
        scanf("%d%d", &a, &b);
        x[a][b] = x[b][a] = 0;
        Union(a, b);
    }
    
    M = 0;
    for (int i = 1; i <= N; ++i)
     for (int j = 1; j <= N; ++j)
      if (x[i][j] > 0) {
          y[M].a = i;
          y[M].b = j;
          y[M].c = x[i][j];
          ++M;
      }
      
    sort(y, y + M);
    
    int ans = 0;
    for (int i = 0; i < M; ++i) {
        int a = y[i].a, b = y[i].b, c = y[i].c;
        a = find(a), b = find(b);
        if (a == b) continue;
        Union(a, b);
        ans += y[i].c;
    }
    
    cout << ans << endl;
    
    return 0;
}
