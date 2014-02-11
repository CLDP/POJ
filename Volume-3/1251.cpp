#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <string>
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
    while (cin >> N) {
        if (N == 0) break;
        
        int nn = 0, M = 0;
        map<string, int> C;
        string P;
        for (int i = 1; i < N; ++i) {
            cin >> P;
            if (C.find(P) == C.end()) C[P] = ++nn;
            int n, a = C[P], b, c;
            cin >> n;
            for (int j = 0; j < n; ++j) {
                cin >> P >> c;
                if (C.find(P) == C.end()) C[P] = ++nn;
                b = C[P];
                y[M].a = a;
                y[M].b = b;
                y[M].c = c;
                ++M;
            }
        }
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
            Union(a, b);
            ans += c;
        }
        
        cout << ans << endl;
    }
    
    return 0;
}
