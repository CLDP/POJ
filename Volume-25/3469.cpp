#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 20010;
const int INF = 1000000000;

vector<pair<int, int> > x[MAXN];
int ff[MAXN], fa[MAXN], h[MAXN], hh[MAXN], fi[MAXN];


// n must be total number of vertices
int max_flow(int s, int t, int n) {
    int i = s, now = INF, ans = 0;
    hh[0] = n;
    
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
    int N, M, a, b, c;
    scanf("%d%d", &N, &M);
    int s = N + 1, t = N + 2, ans = 0;
    x[s].reserve(N);
    for (int i = 1; i <= N; ++i) {
        scanf("%d%d", &a, &b);
        ans += min(a, b);
        if (a == b) continue;
        if (a > b) 
            x[s].push_back(make_pair(i, a - b));
        else 
            x[i].push_back(make_pair(t, b - a));
    }
    for (int i = 0; i < M; ++i) {
        scanf("%d%d%d", &a, &b, &c);
        x[a].push_back(make_pair(b, c));
        x[b].push_back(make_pair(a, c));
    }
    cout << max_flow(s, t, t) + ans << endl;
    return 0;
}

