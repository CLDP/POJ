#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAXN = 50010;
const int INF = 1000000000;

struct EDGE {
    int a, b, c;
    
    bool operator < (EDGE const &B) const {
        return a < B.a;
    }
};

EDGE x[MAXN * 3];
int d[MAXN], s[MAXN];
bool z[MAXN];
int que[1500000];


int make_edge(int a, int b, int c, int &E) {
    x[E].a = a;
    x[E].b = b;
    x[E].c = c;
    ++E;
    return 0;
}


int main() {
    int N, M = 0, E = 0;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        int a, b;
        cin >> a >> b;
        make_edge(a, b + 1, -2, E);
        M = max(M, b + 1);
    }
    for (int i = 0; i <= M; ++i) {
        make_edge(i, i + 1, 0, E);
        make_edge(i + 1, i, 1, E);
        d[i] = INF;
        z[i] = false;
    }
    sort(x, x + E);
    s[0] = 0;
    
    for (int i = 1; i < E; ++i) {
        if (x[i].a == x[i-1].a) continue;
        s[x[i].a] = i;
    }
    
    int l = 0, r = 1;
    d[0] = 0;
    z[0] = true;
    que[0] = 0;
    while (l < r) {
        int a = que[l++];
        for (int i = s[a]; i < s[a + 1]; ++i) {
            if (d[x[i].b] > d[a] + x[i].c) {
                d[x[i].b] = d[a] + x[i].c;
                if (!z[x[i].b]) {
                    z[x[i].b] = true;
                    que[r++] = x[i].b;
                }
            }
        }
        z[a] = false;
    }
    
    cout << -d[M] << endl;
    
    return 0;
}
