#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 210;
const int MAXM = 500;
const int INF = 1000000000;


vector<pair<int, int> > x[MAXN];


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
    int N, NP, NC, M;
    while (cin >> N >> NP >> NC >> M) {
        char trash;
        int s = N + 1, t = N + 2;
        for (int i = 1; i <= t; ++i) x[i].clear();
        int a, b, c;
        for (int i = 0; i < M; ++i) {
            cin >> trash >> a >> trash >> b >> trash >> c;
            x[a + 1].push_back(make_pair(b + 1, c));
        }
        for (int i = 0; i < NP; ++i) {
            cin >> trash >> a >> trash >> b;
            x[s].push_back(make_pair(a + 1, b));
        }
        for (int i = 0; i < NC; ++i) {
            cin >> trash >> a >> trash >> b;
            x[a + 1].push_back(make_pair(t, b));
        }
        cout << max_flow(s, t, t) << endl;
    }
    return 0;
}
