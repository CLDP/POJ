#include <cstdio>
#include <vector>
#include <map>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 510;
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
    cin >> N >> M;
    int s = N + N + 1, t = s + 1, a, b;
    for (int i = 1; i <= N; ++i) {
        cin >> a;
        xx[s].push_back(make_pair(i, a));
    }
    for (int i = 1; i <= N; ++i) {
        cin >> a;
        xx[N + i].push_back(make_pair(t, a));
    }
    for (int i = 0; i < M; ++i) {
        cin >> a >> b;
        xx[b].push_back(make_pair(N + a, INF));
    }
    for (int i = 1; i <= t; ++i) x[i] = xx[i];
    int ans = max_flow(s, t, t);
    cout << ans << endl;
    vector<pair<int, bool> > prev, ansT;
    
    for (int i = 0; i < x[s].size(); ++i) {
        if (x[s][i].second > 0) continue;
        prev.push_back(make_pair(x[s][i].first, false));
    }
    for (int i = N + 1; i <= N + N; ++i) {
        for (int j = 0; j < x[i].size(); ++j) {
            if (x[i][j].first != t || x[i][j].second > 0) continue;
            prev.push_back(make_pair(i - N, true));
        }
    }
    
    for (int i = 0; i < prev.size(); ++i) {
        for (int j = 1; j <= t; ++j) x[j] = xx[j];
        a = prev[i].first;
        int p, q;
        if (prev[i].second) {
            a += N;
            for (int j = 0; j < x[a].size(); ++j)
             if (x[a][j].first == t) {
                 p = a, q = j;
                 b = x[a][j].second;
                 x[a][j].second = 0;
             }
        } else {
            for (int j = 0; j < x[s].size(); ++j) 
             if (x[s][j].first == a) {
                 p = s, q = j;
                 b = x[s][j].second;
                 x[s][j].second = 0;
             }
        }
        if (max_flow(s, t, t) + b == ans) {
            ansT.push_back(prev[i]);
            xx[p][q].second = 0;
            ans -= b;
        }
    }
    
    cout << ansT.size() << endl;
    for (int i = 0; i < ansT.size(); ++i) {
        cout << ansT[i].first << " ";
        cout << (ansT[i].second ? "-" : "+") << endl;
    }
    
    return 0;
}
