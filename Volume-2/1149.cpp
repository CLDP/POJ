#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 510;
const int INF = 1000000000;

struct node {
    int a, b, c;
    
    node(int _a, int _b, int _c) : a(_a), b(_b), c(_c) {}
};

vector<pair<int, int> > x[MAXN];
int y[MAXN], f[MAXN], sum[MAXN];


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


int main() {
    int M, N;
    cin >> M >> N;
    for (int i = 1; i <= M; ++i) cin >> y[i];
    for (int i = 1; i <= N; ++i) {
        int a, b;
        cin >> a;
        for (int j = 0; j < a; ++j) {
            cin >> b;
            if (f[b] == 0) {
                f[b] = i;
                x[N + 1].push_back(make_pair(i, y[b]));
                sum[i] += y[b];
            } else {
                x[f[b]].push_back(make_pair(i, sum[f[b]]));
                sum[i] += sum[f[b]];
            }
        }
        cin >> a;
        x[i].push_back(make_pair(N + 2, a));
    }
    
    cout << max_flow(N + 1, N + 2, N + 2) << endl;
    
    return 0;
}

