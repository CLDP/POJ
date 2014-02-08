#include <cstdio>
#include <vector>
#include <map>
#include <string>
#include <cstring>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 100;
const int MAXP = 11;
const int INF = 1000000000;


vector<pair<int, int> > x[MAXN];
int z[MAXP][MAXP];


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
    string P;
    getline(cin, P);
    while (times--) {
        getline(cin, P);
        istringstream pin(P);
        int a;
        vector<int> X;
        while (pin >> a) X.push_back(a);
        sort(X.begin(), X.end());
        
        int N = X.size(), M = N * (N - 1) / 2;
        int s = N + M + 1, t = s + 1;
        
        memset(z, 0, sizeof(z));
        int count = 0;
        for (int i = 1; i <= N; ++i)
         for (int j = i + 1; j <= N; ++j) z[i][j] = ++count;
         
        bool flag = false;
        for (int k = N; k >= 1; --k) {
            vector<bool> C(N - k, false);
            for (int j = 0; j < k; ++j) C.push_back(true);
            
            bool flagT = false;
            while (!C[0] || flag || k == N) {
                for (int i = 1; i <= t; ++i) x[i].clear();
                for (int i = 1; i <= N; ++i) x[M + i].push_back(make_pair(t, X[i - 1]));
                for (int i = 1; i <= N; ++i)
                 for (int j = i + 1; j <= N; ++j) {
                     x[s].push_back(make_pair(z[i][j], 1));
                     x[z[i][j]].push_back(make_pair(M + i, 1));
                     if (!C[i - 1] || X[i - 1] == X[j - 1]) x[z[i][j]].push_back(make_pair(M + j, 1));
                 }
                if (max_flow(s, t, t) == M) {
                    flag = true;
                    break;
                }
                next_permutation(C.begin(), C.end());
                if (C[0]) flagT = true;
                if (flag && !C[0]) break;
                if (k == N) break;
            }
            if (flag) {
                cout << k << endl;
                break;
            }
        }
    }
    return 0;
}
