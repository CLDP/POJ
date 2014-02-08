#include <cstdio>
#include <vector>
#include <map>
#include <string>
#include <cstring>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 2000;
const int INF = 1000000000;


vector<pair<int, int> > x[MAXN], xx[MAXN];


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
    int N, M;
    while (cin >> N >> M) {
        if (N == 0) break;
        int s = N + M + 1, t = s + 1;
        for (int i = 1; i <= t; ++i) xx[i].clear();
        string P;
        getline(cin, P);
        for (int i = 1; i <= N; ++i) {
            getline(cin, P);
            istringstream input(P);
            string q;
            int a;
            input >> q;
            while (input >> a) {
                xx[i].push_back(make_pair(N + a + 1, 1));
            }
            xx[s].push_back(make_pair(i, 1));
        }
        
        int L = 0, R = N;
        while (L + 1 < R) {
            int mid = (L + R) >> 1;
            for (int i = 1; i <= t; ++i) x[i] = xx[i];
            for (int i = N + 1; i <= N + M; ++i) x[i].push_back(make_pair(t, mid));
            if (max_flow(s, t, t) == N) R = mid; else L = mid;
        }
        
        cout << R << endl;
    }
    return 0;
}
