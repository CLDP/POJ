#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <string>
#include <cmath>
#include <map>
#include <algorithm>
using namespace std;

const int MAXN = 1100;
const int INF = 1000000000;

struct line {
    int a, b, c;
    bool flag;
    
    line(int _a, int _b, int _c, bool _f) : a(_a), b(_b), c(_c), flag(_f) {}
    
    bool operator < (line const &B) const {
        if (B.flag && !flag) return true;
        if (flag && !B.flag) return false;
        return c < B.c;
    }
};


int d[MAXN], f[MAXN], dist[MAXN], fa[MAXN];
vector<line> Y;
vector<line> YY;
vector<pair<int, int> > x[MAXN];


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

int calculate_dist(int a, int D, int f) {
    dist[a] = D;
    for (int i = 0; i < x[a].size(); ++i)
     if (x[a][i].first != f) {
         calculate_dist(x[a][i].first, max(x[a][i].second, D), a);
         fa[x[a][i].first] = a;
     }
    return 0;
}

int remove_edge(int a, int b) {
    for (int i = 0; i < x[a].size(); ++i) {
        if (x[a][i].first == b) {
            x[a].erase(x[a].begin() + i);
            break;
        }
    }
    return 0;
}


int main() {
    int M, N = 1, K;
    cin >> M;
    
    map<string, int> C;
    C["Park"] = 1;
    for (int i = 0; i < M; ++i) {
        string p, q;
        int a, b, c;
        cin >> p >> q >> c;
        if (C.find(p) == C.end()) C[p] = ++N;
        if (C.find(q) == C.end()) C[q] = ++N;
        a = C[p], b = C[q];
        if (a > b) swap(a, b);
        Y.push_back(line(a, b, c, a == 1 || b == 1));
    }
    cin >> K;
    sort(Y.begin(), Y.end());
    for (int i = 1; i <= N; ++i) {
        f[i] = i;
        d[i] = 1;
    }
    
    int ans = 0, prev = -1, num = 0;
    for (int i = 0; i < M; ++i) {
        if (Y[i].flag && prev == -1) prev = i;
        int a = find(Y[i].a), b = find(Y[i].b);
        if (a == b) {
            if (Y[i].flag) YY.push_back(Y[i]);
            continue;
        }
        ans += Y[i].c;
        Union(a, b);
        a = Y[i].a, b = Y[i].b;
        // This guarantee that the longest distance is not from 1
        if (a == 1) Y[i].c = 0;
        x[a].push_back(make_pair(b, Y[i].c));
        x[b].push_back(make_pair(a, Y[i].c));
        if (Y[i].flag) ++num;
    }
    
    int total = ans;
    while (num < K) {
        if (YY.empty()) break;
        calculate_dist(1, 0, -1);
        int temp = INF, p = -1;
        for (int i = 0; i < YY.size(); ++i) {
            int a = YY[i].a, b = YY[i].b;
            if (YY[i].c - dist[b] < temp) {
                temp = YY[i].c - dist[b];
                p = i;
            }
        }
        total += temp;
        if (total < ans) ans = total;
        int b = YY[p].b, c = YY[p].c;
        
        while (b != 1) {
            int a = fa[b];
            if (dist[a] != dist[b]) {
                remove_edge(a, b);
                remove_edge(b, a);
                break;
            }
            b = a;
        }
        b = YY[p].b;
        x[1].push_back(make_pair(b, 0));
        x[b].push_back(make_pair(1, 0));
        YY.erase(YY.begin() + p);
        ++num;
    }
    
    cout << "Total miles driven: " << ans << endl;
    
    return 0;
}
