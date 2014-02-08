#include <cstdio>
#include <vector>
#include <map>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 310;
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
    int N, M, T;
    cin >> N;
    map<string, int> P;
    for (int i = 0; i < N; ++i) {
        string p;
        cin >> p;
        P[p] = i + 1;
    }
    cin >> M;
    int s = N + M + M + 1, t = s + 1;
    for (int i = 1; i <= N; ++i) x[s].push_back(make_pair(i, 1));
    
    int nn = N;
    for (int i = 0; i < M; ++i) {
        string p, q;
        cin >> p >> q;
        if (P.find(q) == P.end()) {
            P[q] = ++nn;
        }
        x[P[q]].push_back(make_pair(N + M + i + 1, 1));
        x[N + M + i + 1].push_back(make_pair(t, 1));
    }
    cin >> T;
    for (int i = 0; i < T; ++i) {
        string p, q;
        cin >> p >> q;
        x[P[q]].push_back(make_pair(P[p], INF));
    }
    cout << M - max_flow(s, t, t) << endl;
    
    return 0;
}
