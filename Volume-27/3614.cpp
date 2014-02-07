#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 5100;
const int INF = 1000000000;

vector<pair<int, int> > x[MAXN];
int minF[MAXN], maxF[MAXN];

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
    int C, L;
    cin >> C >> L;
    int s = C + L + 1, t = s + 1;
    for (int i = 1; i <= C; ++i) {
        cin >> minF[i] >> maxF[i];
        x[L + i].push_back(make_pair(t, 1));
    }
    for (int i = 1; i <= L; ++i) {
        int a, b;
        cin >> a >> b;
        x[s].push_back(make_pair(i, b));
        for (int j = 1; j <= C; ++j) 
         if (minF[j] <= a && a <= maxF[j]) x[i].push_back(make_pair(L + j, 1));
    }
    cout << max_flow(s, t, t) << endl;
    return 0;
}
