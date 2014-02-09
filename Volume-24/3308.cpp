#include <cstdio>
#include <vector>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1000;
const int INF = 1000000000;


vector<pair<int, double> > x[MAXN];


// n must be total number of vertices
double max_flow(int s, int t, int n) {
    vector<double> ff(n + 1, 0);
    vector<int> fa(n + 1, 0);
    vector<int> h(n + 1, 0);
    vector<int> hh(n + 1, 0);
    vector<int> fi(n + 1, 0);
    
    int i = 0;
    double ans = 0;
    hh[0] = n;
    
    i = s;
    double now = INF;
    
    while (h[s] < n) {
        ff[i] = now;
        bool flag = false;
        vector<pair<int, double> >::iterator p = x[i].begin();
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
        
        int min = n - 1;
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
        int N, M, K;
        cin >> N >> M >> K;
        int s = N + M + 1, t = s + 1;
        for (int i = 1; i <= t; ++i) x[i].clear();
        double a;
        for (int i = 1; i <= N; ++i) {
            cin >> a;
            x[s].push_back(make_pair(i, log(a)));
        }
        for (int i = 1; i <= M; ++i) {
            cin >> a;
            x[N + i].push_back(make_pair(t, log(a)));
        }
        for (int i = 0; i < K; ++i) {
            int b, c;
            cin >> b >> c;
            x[b].push_back(make_pair(N + c, INF));
        }
        double ans = max_flow(s, t, t);
        ans = exp(ans);
        printf("%.4lf\n", ans);
    }
    
    return 0;
}
