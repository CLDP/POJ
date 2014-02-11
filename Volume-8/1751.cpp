#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 1001;
const int MAXM = 300010;
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
int p[MAXN], q[MAXN];


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
    int N;
    cin >> N;
    for (int i = 1; i <= N; ++i) cin >> p[i] >> q[i];
    
    int M = 0;
    for (int i = 1; i <= N; ++i)
     for (int j = i + 1; j <= N; ++j) {
         y[M].a = i;
         y[M].b = j;
         y[M].c = (p[i] - p[j]) * (p[i] - p[j]) + (q[i] - q[j]) * (q[i] - q[j]);
         ++M;
     }
    sort(y, y + M);
    
    int T;
    cin >> T;
    for (int i = 1; i <= N; ++i) {
        d[i] = 1;
        f[i] = i;
    }
    
    for (int i = 0; i < T; ++i) {
        int a, b;
        cin >> a >> b;
        Union(a, b);
    }
    
    for (int i = 0; i < M; ++i) {
        int a = y[i].a, b = y[i].b, c = y[i].c;
        a = find(a), b = find(b);
        if (a == b) continue;
        Union(a, b);
        cout << y[i].a << " " << y[i].b << endl;
    }
    
    return 0;
}
