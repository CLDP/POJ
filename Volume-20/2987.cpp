#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 6100;
const int INF = 1000000000;

vector<pair<int, int> > x[MAXN];
bool z[MAXN];

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

int dfs(int a, int &num) {
    z[a] = true;
    ++num;
    for (int i = 0; i < x[a].size(); ++i) {
        if (z[x[a][i].first] || x[a][i].second == 0) continue;
        dfs(x[a][i].first, num);
    }
    return 0;
}


int main() {
    int N, M, a, b;
    scanf("%d%d", &N, &M);
    int s = N + 1, t = N + 2;
    long long ans = 0;
    for (int i = 1; i <= N; ++i) {
        scanf("%d", &a);
        if (a > 0) {
            x[s].push_back(make_pair(i, a)); 
            ans += a;
        } else {
            x[i].push_back(make_pair(t, -a));
        }
    }
    for (int i = 0; i < M; ++i) {
        scanf("%d%d", &a, &b);
        x[a].push_back(make_pair(b, INF));
    }
    ans -= max_flow(s, t, t);
    int num = -1;
    dfs(s, num);
    cout << num << " " << ans << endl;
    
    return 0;
}
