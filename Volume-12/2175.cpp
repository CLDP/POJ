#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 501;
const int INF = 1000000000;


struct node {
    int v, w, f;
    
    node(int _v, int _w, int _f) : v(_v), w(_w), f(_f) {}
};

struct pos {
    int x, y, n;
    
    pos(int _x, int _y, int _n) : x(_x), y(_y), n(_n) {}
};


vector<node> x[MAXN];
vector<pos> y1, y2;
int f[MAXN][MAXN];


int dist(int a, int b) {
    return abs(y1[a].x - y2[b].x) + abs(y1[a].y - y2[b].y) + 1;
}


int SPFA(int N, int NN, vector<int> &f) {
    vector<int> d(N + 1, 0);
    vector<bool> z(N + 1, true);
    vector<int> T(N + 1, 0);
    f = vector<int> (N + 1, 0);
    
    queue<int> que;
    for (int i = 1; i <= N; ++i) que.push(i);
    
    while (!que.empty()) {
        int a = que.front();
        que.pop();
        for (int i = 0; i < x[a].size(); ++i) {
            if (d[x[a][i].v] > d[a] + x[a][i].w) {
                f[x[a][i].v] = a;
                d[x[a][i].v] = d[a] + x[a][i].w;
                
                if (!z[x[a][i].v]) {
                    z[x[a][i].v] = true;
                    ++T[x[a][i].v];
                    if (T[x[a][i].v] == N && x[a][i].v > NN) return x[a][i].v;
                    que.push(x[a][i].v);
                }
            }
        }
        z[a] = false;
    }
    
    return 0;
}

int main() {
    int N, M;
    cin >> N >> M;
    for (int i = 0; i < N; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        y1.push_back(pos(a, b, c));
    }
    for (int i = 0; i < M; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        y2.push_back(pos(a, b, c));
    }
    for (int i = 0; i < N; ++i)
     for (int j = 0; j < M; ++j) {
         cin >> f[i][j];
         if (f[i][j] > 0)
             x[N + j + 1].push_back(node(i + 1, -dist(i, j), f[i][j]));
         x[i + 1].push_back(node(N + j + 1, dist(i, j), INF));
     }
    
    int t = N + M + 1;
    for (int j = N + 1; j <= N + M; ++j) {
        int temp = y2[j - N - 1].n;
        for (int i = 0; i < N; ++i) temp -= f[i][j - N - 1];
        if (temp > 0) x[j].push_back(node(t, 0, temp));
        if (y2[j - N - 1].n > temp) x[t].push_back(node(j, 0, y2[j - N - 1].n - temp));
    }
    
    bool flag = false;
    vector<int> fa;
    int a = SPFA(t, N, fa), b = -1;
    if (a > 0) {
        flag = true;
        vector<bool> z(t + 1, false);
        while (!z[a]) {
            z[a] = true;
            a = fa[a];
        }
        int c = a;
        while (true) {
            b = a;
            a = fa[b];
            if (a == 0 || b == 0) break;
            if (a > N) {
                --f[b - 1][a - N - 1];
            } else {
                ++f[a - 1][b - N - 1];
            }
            if (a == c) break;
        }
    }
    
    if (flag) {
        cout << "SUBOPTIMAL" << endl;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M - 1; ++j) cout << f[i][j] << " "; 
            cout << f[i][M - 1] << endl;
        }
    } else {
        cout << "OPTIMAL" << endl;
    }
    
    return 0;
}
