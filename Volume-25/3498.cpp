#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 110;
const int MAXM = 500;
const int INF = 1000000000;

struct node {
    double a, b;
    int n, m;
};

vector<pair<int, int> > x[MAXM], xx[MAXM];
node y[MAXN];
bool z[MAXN][MAXN];


// n must be total number of vertices
long long max_flow(int s, int t, int n) {
    vector<int> ff(n + 1, 0);
    vector<int> fa(n + 1, 0);
    vector<int> h(n + 1, 0);
    vector<int> hh(n + 1, 0);
    vector<int> fi(n + 1, 0);
    
    int i = 0, now;
    long long ans = 0;
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
    int times;
    cin >> times;
    while (times--) {
        int N, total = 0;
        double R;
        cin >> N >> R;
        for (int i = 0; i < N; ++i) cin >> y[i].a >> y[i].b >> y[i].n >> y[i].m;
        int s = N + N + 1, t = s + 1;
        for (int i = 1; i <= t; ++i) xx[i].clear();
        
        for (int i = 1; i <= N; ++i) {
            total += y[i - 1].n;
            xx[s].push_back(make_pair(i, y[i - 1].n));
            xx[i].push_back(make_pair(N + i, y[i - 1].m));
            for (int j = 0; j < N; ++j) {
                if (j + 1 == i) continue;
                if ((y[j].a - y[i-1].a) * (y[j].a - y[i-1].a) + 
                    (y[j].b - y[i-1].b) * (y[j].b - y[i-1].b) <= R * R) {
                    xx[N + i].push_back(make_pair(j + 1, INF));
                    xx[N + j + 1].push_back(make_pair(i, INF));
                }
            }
        }
        
        vector<int> ans;
        for (int i = 0; i < N; ++i) {
            for (int j = 1; j <= t; ++j) x[j] = xx[j];
            x[i + 1].push_back(make_pair(t, INF));
            if (max_flow(s, t, t) == total) ans.push_back(i);
        }
        if (ans.size() == 0) {
            cout << -1 << endl;
        } else {
            for (int i = 0; i < ans.size() - 1; ++i) cout << ans[i] << " ";
            cout << ans[ans.size() - 1] << endl;
        }
    }
    
    return 0;
}
