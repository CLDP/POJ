#include <cstdio>
#include <vector>
#include <map>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 110;
const int INF = 1000000000;


vector<pair<int, int> > x[MAXN], xx[MAXN];


// n must be total number of vertices
int max_flow(int s, int t, int n) {
    vector<int> ff(n + 1, 0);
    vector<int> fa(n + 1, 0);
    vector<int> h(n + 1, 0);
    vector<int> hh(n + 1, 0);
    vector<int> fi(n + 1, 0);
    
    int i = 0, now;
    int ans = 0;
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
    while (cin >> N >> M) {
        if (N == 0 || N == 1) {
            cout << N << endl;
            continue;
        }
        if (M < N - 1) {
            cout << 0 << endl;
            continue;
        }
        for (int i = 1; i <= N + N; ++i) xx[i].clear();
        for (int i = 1; i <= N; ++i) xx[i].push_back(make_pair(N + i, 1));
        char trash;
        int a, b;
        for (int i = 0; i < M; ++i) {
            cin >> trash >> a >> trash >> b >> trash;
            xx[N + a + 1].push_back(make_pair(b + 1, INF));
            xx[N + b + 1].push_back(make_pair(a + 1, INF));
        }
        int ans = INF;
        for (int i = 1; i < N; ++i)
         for (int j = i + 1; j <= N; ++j) {
             for (int k = 1; k <= N + N; ++k) x[k] = xx[k];
             ans = min(ans, max_flow(N + i, j, N + N));
         }
        
        if (ans == INF) ans = N;
        cout << ans << endl;
    }
    
    return 0;
}
