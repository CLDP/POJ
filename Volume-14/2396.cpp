#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 500;
const int INF = 1000000000;

vector<pair<int, int> > x[MAXN];
int upbound[300][30], lowbound[300][30];


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

int change(int i, int j, int c, char p) {
    if (p == '=') {
        upbound[i][j] = min(upbound[i][j], c);
        lowbound[i][j] = max(lowbound[i][j], c);
    } else
    if (p == '>') {
        lowbound[i][j] = max(lowbound[i][j], c + 1);
    } else {
        upbound[i][j] = min(upbound[i][j], c - 1);
    }
    return 0;
}


int main() {
    int times;
    cin >> times;
    while (times--) {
        int N, M, a;
        cin >> N >> M;
        int s = N + M + 1, t = s + 1;
        for (int i = 1; i <= t; ++i) x[i].clear();
        vector<int> R(N + 1, 0), C(M + 1, 0);
        
        for (int i = 0; i < N; ++i) cin >> R[i];
        for (int j = 0; j < M; ++j) cin >> C[j];
        
        for (int i = 0; i < N; ++i) 
         for (int j = 0; j < M; ++j) {
             upbound[i][j] = INF;
             lowbound[i][j] = 0;
         }
        
        int T, b, c;
        char p;
        cin >> T;
        bool flag = true;
        for (int k = 0; k < T; ++k) {
            cin >> a >> b >> p >> c;
            if (a == 0 && b == 0) {
                for (int i = 0; i < N; ++i)
                 for (int j = 0; j < M; ++j) change(i, j, c, p);
            }
            if (a == 0 && b != 0) {
                for (int i = 0; i < N; ++i) change(i, b - 1, c, p);
            }
            if (a != 0 && b == 0) {
                for (int j = 0; j < M; ++j) change(a - 1, j, c, p);
            } 
            if (a != 0 && b != 0) {
                change(a - 1, b - 1, c, p);
            }
        }
        for (int i = 0; i < N; ++i)
         for (int j = 0; j < M; ++j) 
          if (upbound[i][j] < lowbound[i][j]) flag = false;
        
        if (!flag) {
            cout << "IMPOSSIBLE" << endl;
            if (times != 0) cout << endl;
            continue;
        }
        
        
        for (int i = 0; i < N; ++i)
         for (int j = 0; j < M; ++j) {
             R[i] -= lowbound[i][j];
             C[j] -= lowbound[i][j];
         }
         
        int total = 0;
        for (int i = 1; i <= N; ++i) {
            if (R[i - 1] < 0) flag = false;
            total += R[i - 1];
            x[s].push_back(make_pair(i, R[i - 1]));
        }
        for (int j = 1; j <= M; ++j) {
            if (C[j - 1] < 0) flag = false;
            x[N + j].push_back(make_pair(t, C[j - 1]));
        }
        if (!flag) {
            cout << "IMPOSSIBLE" << endl;
            if (times != 0) cout << endl;
            continue;
        }
        
        for (int i = 0; i < N; ++i)
         for (int j = 0; j < M; ++j) {
             x[i + 1].push_back(make_pair(N + j + 1, upbound[i][j] - lowbound[i][j]));
         }
        
        int ans = max_flow(s, t, t);
        if (ans != total) {
            cout << "IMPOSSIBLE" << endl;
            if (times != 0) cout << endl;
            continue;
        }
        
        for (int i = 1; i <= N; ++i) {
            for (int j = 0; j < M; ++j) upbound[i - 1][j] -= x[i][j].second;
            for (int j = M; j < x[i].size(); ++j)
             if (x[i][j].first > N && x[i][j].first <= N + M) upbound[i - 1][x[i][j].first - N - 1] -= x[i][j].second;
        }
        
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) cout << upbound[i][j] << " ";
            cout << endl;
        }
        
        if (times != 0) cout << endl;
    }

    
    return 0;
}
