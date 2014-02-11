#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <string>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 110;
const int INF = 1000000000;


vector<pair<int, int> > x[MAXN];




int main() {
    int N, M;
    while (cin >> N >> M) {
        if (N == 0) break;
        for (int i = 0; i <= N; ++i) x[i].clear();
        
        vector<int> d(N + 1, INF);
        vector<bool> z(N + 1, false);
        vector<int> num(N + 1, 0);
        queue<int> que;
        for (int i = 0; i < M; ++i) {
            int a, b, c;
            string p;
            cin >> a >> b >> p >> c;
            if (p == "gt") {
                x[a + b].push_back(make_pair(a - 1, -c - 1));
                if (!z[a + b]) que.push(a + b);
                z[a + b] = true;
                d[a + b] = 0;
            } else {
                x[a - 1].push_back(make_pair(a + b, c - 1));
                if (!z[a - 1]) que.push(a - 1);
                z[a - 1] = true;
                d[a - 1] = 0;
            }
        }
        
        bool flag = true;
        while (!que.empty()) {
            int a = que.front();
            que.pop();
            if (num[a] > N) {
                flag = false;
                break;
            }
            
            for (int i = 0; i < x[a].size(); ++i) {
                if (d[x[a][i].first] > d[a] + x[a][i].second) {
                    d[x[a][i].first] = d[a] + x[a][i].second;
                    if (!z[x[a][i].first]) {
                        z[x[a][i].first] = true;
                        que.push(x[a][i].first);
                        ++num[x[a][i].first];
                    }
                }
            }
            
            z[a] = false;
        }
        
        if (flag) 
            cout << "lamentable kingdom" << endl; 
        else 
            cout << "successful conspiracy" << endl;
        
    }
    return 0;
}
