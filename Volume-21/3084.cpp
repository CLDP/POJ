#include <cstdio>
#include <vector>
#include <map>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 110;
const int INF = 100000;


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
    int times;
    cin >> times;
    while (times--) {
        int N, K;
        cin >> N >> K;
        int s = N + 1, t = K + 1;
        for (int i = 1; i <= s; ++i) x[i].clear();
        
        for (int i = 1; i <= N; ++i) {
            string P;
            int M, a;
            cin >> P >> M;
            if (P == "I") x[s].push_back(make_pair(i, INF));
            for (int j = 0; j < M; ++j) {
                cin >> a;
                x[i].push_back(make_pair(a + 1, INF));
                x[a + 1].push_back(make_pair(i, 1));
            }
        }
        int ans = max_flow(s, t, s);
        if (ans >= INF) 
            cout << "PANIC ROOM BREACH" << endl;
        else 
            cout << ans << endl;
    }
    
    return 0;
}
