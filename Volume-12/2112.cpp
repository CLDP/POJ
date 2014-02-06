#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 250;
const int INF = 1000000000;

vector<pair<int, int> > x[MAXN];
int y[MAXN][MAXN];


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
    int K, C, M;
    cin >> K >> C >> M;
    for (int i = 0; i < K + C; ++i)
     for (int j = 0; j < K + C; ++j) {
         cin >> y[i][j];
         if (i != j && y[i][j] == 0) y[i][j] = INF;
     }
    
    for (int k = 0; k < K + C; ++k)
     for (int i = 0; i < K + C; ++i)
      for (int j = 0; j < K + C; ++j) 
       if (y[i][k] + y[k][j] < y[i][j]) y[i][j] = y[i][k] + y[k][j];
    
    int L = 0, R = 0;
    for (int i = 0; i < K; ++i)
     for (int j = K; j < K + C; ++j)
      if (y[i][j] > R) R = y[i][j];
    
    while (L + 1 < R) {
        int mid = (L + R) >> 1;
        for (int i = 1; i <= K + C + 2; ++i) x[i].clear();
        int s = K + C + 1, t = s + 1;
        for (int i = 1; i <= K; ++i) x[s].push_back(make_pair(i, M));
        for (int i = K + 1; i <= K + C; ++i) x[i].push_back(make_pair(t, 1));
        for (int i = 1; i <= K; ++i)
         for (int j = K + 1; j <= K + C; ++j) 
          if (y[i-1][j-1] <= mid) x[i].push_back(make_pair(j, 1));
        
        if (max_flow(s, t, t) == C) R = mid; else L = mid;
    }
    
    cout << R << endl;
    
    return 0;
}

