#include <iostream>
#include <vector>
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 1100;
const int MAXM = 21;
const int INF = 1000000000;


vector<pair<int, int> > x[MAXN];
int y[MAXM], z[MAXN][MAXM];


// n must be total number of vertices
int max_flow(int s, int t, int n) {
    vector<int> ff(n + 1, 0);
    vector<int> fa(n + 1, 0);
    vector<int> h(n + 1, 0);
    vector<int> hh(n + 1, 0);
    vector<int> fi(n + 1, 0);
    
    int i = 0, now, ans = 0;
    hh[0] = n;
    
    i = s;
    now = INF;
    
    while (h[s] < n) {
        ff[i] = now;
        bool flag = false;
        vector<pair<int, int> >::iterator p = x[i].begin();
        while (p != x[i].end()) {
            if (p->second > 0 && h[p->first] + 1 == h[i]) {
                flag = true;
                if (p->second < now) now = p->second;
                fa[p->first] = i;
                fi[p->first] = p - x[i].begin();
                i = p->first;
                if (i == t) {
                    ans += now;
                    while (i != s) {
                        int tmp = i;
                        i = fa[i];
                        p = x[i].begin() + fi[tmp];
                        p->second -=now;
                        x[tmp].push_back(make_pair(i, now));
                    }
                    now = INF;
                }
                break;
            }
            ++p;
        }
        if (flag) continue;
        
        int min = n-1;
        p = x[i].begin();
        while (p != x[i].end()) {
            if (p->second > 0 && h[p->first] < min) min = h[p->first];
            ++p;
        }
        
        --hh[h[i]];
        if (hh[h[i]] == 0) break;
        h[i] = min + 1;
        ++hh[h[i]];
        if (i != s) {
            i = fa[i];
            now = ff[i];
        }
    }
    
    return ans;
}

int main() {
    int N, M;
    cin >> N >> M;
    for (int i = 0; i < N; ++i)
     for (int j = 0; j < M; ++j) cin >> z[i][j];
    for (int i = 0; i < M; ++i) cin >> y[i];
    
    int s = N + M + 1, t = s + 1;
    for (int i = 0; i < M; ++i) {
        bool flag = false;
        for (int j = 1; j <= M - i; ++j) {
            for (int k = 1; k <= t; ++k) x[k].clear();
            for (int k = 0; k < N; ++k) {
                for (int l = j - 1; l <= j - 1 + i; ++l) {
                    x[k + 1].push_back(make_pair(N + z[k][l], 1)); 
                }
            }
            for (int k = 1; k <= N; ++k) x[s].push_back(make_pair(k, 1));
            for (int l = 1; l <= M; ++l) x[N + l].push_back(make_pair(t, y[l - 1]));
            if (max_flow(s, t, t) == N) flag = true;
            if (flag) break;
        }
        if (flag) {
            cout << i + 1 << endl;
            break;
        }
    }
    
    return 0;
}
