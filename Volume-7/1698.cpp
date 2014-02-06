#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 1000;
const int INF = 1000000000;

vector<pair<int, int> > x[MAXN];
int y[21][7], D[21], W[21];


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
        // if (!flag && i == s) break;
        
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
        int M, N, T = 0, sum = 0;
        cin >> M;
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < 7; ++j) cin >> y[i][j];
            cin >> D[i] >> W[i];
            T = max(T, W[i]);
            sum += D[i];
        }
        int s = 14 * T + 2 * M + 1, t = s + 1;
        
        for (int i = 0; i <= t; ++i) x[i].clear();
        
        for (int i = 0; i < 7 * T; ++i) x[2 * i + 1].push_back(make_pair(2 * i + 2, 1));
         
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < 7; ++j) {
                if (y[i][j] == 0) continue;
                for (int k = 0; k < W[i]; ++k) {
                    x[14 * T + 2 * i + 1].push_back(make_pair(14 * k + 2 * j + 1, 1));
                    x[14 * k + 2 * j + 2].push_back(make_pair(14 * T + 2 * i + 2, 1));
                } 
            }
            x[s].push_back(make_pair(14 * T + 2 * i + 1, D[i]));
            x[14 * T + 2 * i + 2].push_back(make_pair(t, D[i]));
        }
        if (max_flow(s, t, t) == sum) cout << "Yes" << endl; else cout << "No" << endl;
    }
    return 0;
}
