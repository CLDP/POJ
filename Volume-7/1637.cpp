#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 3000;
const int INF = 1000000000;

struct node {
    int a, b, c;
};

vector<pair<int, int> > x[MAXN];
node y[MAXN];
int in[MAXN];


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
        int N, M;
        cin >> N >> M;
        memset(in, 0, sizeof(in));
        bool flag = true;
        for (int i = 0; i < M; ++i) {
            cin >> y[i].a >> y[i].b >> y[i].c;
            if (y[i].c == 1) {
                ++in[y[i].b];
                --in[y[i].a];
                flag = false;
            } 
        }
        if (flag) {
            y[0].c = 1;
            ++in[y[0].b];
            --in[y[0].a];
        }
        int s = N + M + 1, t = s + 1, total = 0;
        for (int i = 1; i <= t; ++i) x[i].clear();
        for (int i = 1; i <= N; ++i) {
            if (in[i] > 0) {
                x[i].push_back(make_pair(t, in[i]));
                total += in[i];
            }
            if (in[i] < 0) x[s].push_back(make_pair(i, -in[i]));
        }
        for (int i = 0; i < M; ++i) {
            if (y[i].c == 1) continue;
            x[y[i].a].push_back(make_pair(N + i + 1, 1));
            x[y[i].b].push_back(make_pair(N + i + 1, 1));
            x[N + i + 1].push_back(make_pair(y[i].a, 1));
            x[N + i + 1].push_back(make_pair(y[i].b, 1));
        }
        
        if (max_flow(s, t, t) != total) cout << "im";
        cout << "possible" << endl;
    }
    
    return 0;
}
