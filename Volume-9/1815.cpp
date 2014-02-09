#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1000;
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
    int N, P1, P2, a;
    cin >> N >> P1 >> P2;
    for (int i = 1; i <= N; ++i)
     for (int j = 1; j <= N; ++j) {
         cin >> a;
         if (i == j) continue;
         if (a == 1) {
             if ((i == P1 && j == P2) || (i == P2 && j == P1)) {
                 cout << "NO ANSWER!" << endl;
                 return 0;
             }
             x[N + i].push_back(make_pair(j, 1));
             xx[N + i].push_back(make_pair(j, 1));
         }
     }
    for (int i = 1; i <= N; ++i) {
        x[i].push_back(make_pair(N + i, 1));
        xx[i].push_back(make_pair(N + i, 1));
    }
    
    int s = N + P1, t = P2, ans = max_flow(s, t, N + N);
    cout << ans << endl;
    
    vector<int> prev;
    for (int i = 1; i <= N; ++i) 
     for (int j = 0; j < x[i].size(); ++j) 
      if (x[i][j].first == N + i && x[i][j].second == 0) prev.push_back(i);
    
    for (int i = 0; i < prev.size(); ++i) {
        int r = prev[i];
        for (int j = 0; j < xx[r].size(); ++j)
         if (xx[r][j].first == r + N) xx[r][j].second = 0;
         
        for (int j = 1; j <= N + N; ++j) x[j] = xx[j];
        
        int temp = max_flow(s, t, N + N);
        if (temp == ans - 1) {
            cout << r;
            --ans;
            if (ans == 0) cout << endl; else cout << " ";
        } else {
            for (int j = 0; j < xx[r].size(); ++j)
             if (xx[r][j].first == r + N) xx[r][j].second = 1;
        }
    }
    
    return 0;
}
