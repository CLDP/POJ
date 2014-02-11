#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAXN = 1001;
const int MAXM = 500010;
const int INF = 1000000000;

struct line {
    int a, b;
    double c;
    bool operator < (line const &B) const {
        return c < B.c;
    }
};


line y[MAXM];
int d[MAXN], f[MAXN];
double p[MAXN], q[MAXN];


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
    int N, T;
    cin >> N >> T;
    for (int i = 1; i <= N; ++i) cin >> p[i] >> q[i];
    
    int M = 0;
    for (int i = 1; i <= N; ++i)
     for (int j = i + 1; j <= N; ++j) {
         y[M].a = i;
         y[M].b = j;
         y[M].c = sqrt((p[i] - p[j]) * (p[i] - p[j]) + (q[i] - q[j]) * (q[i] - q[j]));
         ++M;
     }
    sort(y, y + M);
    
    for (int i = 1; i <= N; ++i) {
        d[i] = 1;
        f[i] = i;
    }
    for (int i = 0; i < T; ++i) {
        int a, b;
        cin >> a >> b;
        Union(a, b);
    }
    
    double ans = 0;
    for (int i = 0; i < M; ++i) {
        int a = y[i].a, b = y[i].b;
        a = find(a), b = find(b);
        if (a == b) continue;
        Union(a, b);
        ans += y[i].c;
    }
    
    printf("%.2lf\n", ans);
    
    return 0;
}
