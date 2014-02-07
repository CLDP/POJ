#include <iostream>
#include <vector>
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 510;
const int MAXM = 5010;
const int INF = 1000000000;

struct node {
    int a, b, c;
};

int N, M;
vector<pair<int, int> > x[MAXN];
node y[MAXM];
bool z1[MAXM], z2[MAXM], z[MAXN];


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

int dfs_s(int a) {
    z1[a] = true;
    for (int i = 0; i < x[a].size(); ++i) {
        if (z1[x[a][i].first]) continue;
        if (x[a][i].second == 0) continue;
        dfs_s(x[a][i].first);
    }
    return 0;
}

bool dfs_t(int a) {
    z[a] = true;
    if (a == N) {
        z2[N] = true;
        return true;
    }
    for (int i = 0; i < x[a].size(); ++i) {
        if (z2[x[a][i].first]) return z2[a] = true;
        if (z[x[a][i].first]) continue;
        if (x[a][i].second == 0) continue;
        if (dfs_t(x[a][i].first)) return z2[a] = true;
    }
    z2[a] = false;
    return false;
}


int main() {
    cin >> N >> M;
    for (int i = 0; i < M; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        y[i].a = a + 1, y[i].b = b + 1, y[i].c = c;
        x[a + 1].push_back(make_pair(b + 1, c));
    }
    max_flow(1, N, N);
    dfs_s(1);
    for (int i = 1; i <= N; ++i) {
        if (z2[i]) continue;
        dfs_t(i);
    }
    
    int ans = 0;
    for (int i = 0; i < M; ++i) ans += (z1[y[i].a] && z2[y[i].b]);
    
    cout << ans << endl;
    
    return 0;
}
