#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 110;
const int INF = 1000000000;


vector<pair<int, int> > x[MAXN];
int y[MAXN], d[MAXN];
bool z[MAXN];

int main() {
    int K, N;
    cin >> K >> N;
    for (int i = 1; i <= N; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        x[0].push_back(make_pair(i, a));
        y[i] = b;
        for (int j = 0; j < c; ++j) {
            int p, q;
            cin >> p >> q;
            x[p].push_back(make_pair(i, q));
        }
    }
    
    int ans = INF;
    
    for (int k = 1; k <= N; ++k) {
        y[0] = y[k];
        for (int i = 0; i <= N; ++i) {
            d[i] = INF;
            z[i] = false;
            if (y[i] < y[0] || y[i] > y[0] + K) z[i] = true;
        }
        if (z[1]) continue;
        
        d[0] = 0;
        for (int i = 0; i < N; ++i) {
            int a = -1, b = INF;
            for (int j = 0; j <= N; ++j) {
                if (z[j] || d[j] > b) continue;
                a = j;
                b = d[j];
            }
            if (a == -1) break;
            z[a] = true;
            
            for (int j = 0; j < x[a].size(); ++j) {
                if (d[x[a][j].first] > d[a] + x[a][j].second) d[x[a][j].first] = d[a] + x[a][j].second;
            }
        }
        
        ans = min(ans, d[1]);
    }
    
    cout << ans << endl;
    
    return 0;
}
