#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <string>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 1001;
const int INF = 1000000000;

vector<pair<int, int> > x[MAXN];
bool cz[MAXN];

int SPFA(int s, int N) {
    vector<int> d(N + 1, INF);
    vector<int> num(N + 1, 0);
    vector<bool> z(N + 1, false);

    queue<int> que;
    que.push(s);
    z[s] = true;
    d[s] = 0;
    while (!que.empty()) {
        int a = que.front();
        if (num[a] == N + 1) return -1;
        cz[a] = true;
        que.pop();
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
    
    return d[N];
}


int main() {
    int N, M1, M2, a, b, c;
    scanf("%d%d%d", &N, &M1, &M2);
    for (int i = 0; i < M1; ++i) {
        scanf("%d%d%d", &a, &b, &c);
        x[a].push_back(make_pair(b, c));
    }
    for (int i = 0; i < M2; ++i) {
        scanf("%d%d%d", &a, &b, &c);
        x[b].push_back(make_pair(a, -c));
    }
    
    int ans = 0;
    for (int i = 1; i <= N; ++i) {
        if (!cz[i]) {
            int temp = SPFA(i, N);
            if (temp == -1) {
                cout << -1 << endl;
                return 0;
            }
            if (i == 1) ans = temp;
        }
    }
    
    if (ans == INF) ans = -2;
    cout << ans << endl;
    
    return 0;
}
