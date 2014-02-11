#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 2001;
const int MAXM = 20000;
const int INF = 1000000000;

struct line {
    int a, b, c;
    bool operator < (line const &B) const {
        return c < B.c;
    }
};

line y[MAXM];
int d[MAXN], f[MAXN];


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
    int N, M;
    cin >> N >> M;
    for (int i = 0; i < M; ++i) cin >> y[i].a >> y[i].b >> y[i].c;
    sort(y, y + M);
    
    for (int i = 1; i <= N; ++i) {
        d[i] = 1;
        f[i] = i;
    }
    int ans = 0;
    for (int i = 0; i < M; ++i) {
        int a = y[i].a, b = y[i].b, c = y[i].c;
        a = find(a), b = find(b);
        if (a == b) continue;
        ans = max(ans, c);
        Union(a, b);
    }
    
    cout << ans << endl;
    
    return 0;
}
