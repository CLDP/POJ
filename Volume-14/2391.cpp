#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

const int MAXN = 410;
const int INF = 1000000000;
const long long INFL = 1000000000000;


vector<pair<int, int> > x[MAXN];
pair<int, int> y[MAXN];
long long z[MAXN][MAXN];


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


int make_edge(int N, long long R, int &s, int &t, int &n) {
    s = N + N + 1, t = N + N + 2, n = N + N + 2;
    for (int i = 1; i <= n; ++i) x[i].clear();
    
    for (int i = 0; i < N; ++i) {
        x[s].push_back(make_pair(2 * i + 1, y[i].first));
        x[2 * i + 2].push_back(make_pair(t, y[i].second));
    }
    for (int i = 1; i <= N; ++i)
     for (int j = 1; j <= N; ++j) 
      if (z[i][j] <= R) x[2 * i - 1].push_back(make_pair(2 * j, INF));
    return 0;
}

int main() {
    int M, N, total = 0;
    cin >> N >> M;
    for (int i = 0; i < N; ++i) {
        cin >> y[i].first >> y[i].second;
        total += y[i].first;
    }
    
    for (int i = 1; i <= N; ++i)
     for (int j = 1; j <= N; ++j) {
         if (i == j) continue;
         z[i][j] = INFL;
     }
    
    for (int i = 0; i < M; ++i) {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        z[a][b] = z[b][a] = min(z[a][b], c);
    }
    
    for (int k = 1; k <= N; ++k)
     for (int i = 1; i <= N; ++i)
      for (int j = 1; j <= N; ++j)
       if (z[i][k] + z[k][j] < z[i][j]) z[i][j] = z[i][k] + z[k][j];
    
    long long L = 0, R = 0;
    for (int i = 1; i <= N; ++i)
     for (int j = 1; j <= N; ++j) 
      if (z[i][j] < INFL) R = max(R, z[i][j]);
    
    int s, t, n;
    make_edge(N, R, s, t, n);
    if (max_flow(s, t, n) < total) {
        cout << -1 << endl;
        return 0;
    }
    
    while (L + 1 < R) {
        long long mid = (L + R) >> 1;
        make_edge(N, mid, s, t, n);
        if (max_flow(s, t, n) == total) R = mid; else L = mid;
    }
    
    cout << R << endl;
    
    return 0;
}

