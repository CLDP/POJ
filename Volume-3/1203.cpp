#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 100010;
const int INF = 1000000000;

struct node {
    int v, s, t;
    
    node(int v1, int s1, int t1) : v(v1), s(s1), t(t1) {}
};


int N;
vector<node> x[MAXN];
vector<int> f[MAXN];
vector<bool> z[MAXN];

int changeT(char p[]) {
    return (p[0] - '0') * 600 + (p[1] - '0') * 60 + (p[3] - '0') * 10 + (p[4] - '0');
}

string changeTB(int a) {
    if (a == INF) return "-1";
    string res;
    res = res + (char)(a / 600 + '0') + (char)(a / 60 % 10 + '0') + ":";
    a %= 60;
    res = res + (char)(a / 10 + '0') + (char)(a % 10 + '0');
    return res;
}

int dp(int a, int b, int T) {
    if (a == N - 1) return T;
    if (b >= x[a].size()) return INF;
    if (z[a][b]) return f[a][b];
    z[a][b] = true;
    int v = x[a][b].v;
    int t = x[a][b].t;
    
    if (f[a][b] == 0) f[a][b] = INF;
    f[a][b] = min(f[a][b], dp(a, b + 1, T));
    if (v == N - 1) {
        f[a][b] = min(f[a][b], t);
        return f[a][b];
    }
    if (x[v].size() == 0) return f[a][b];
    
    int l = 0, r = x[v].size() - 1;
    if (x[v][r].s < t) return f[a][b];
    if (x[v][l].s >= t) {
        r = 0;
    } else {
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            if (x[v][mid].s >= t) r = mid; else l = mid;
        }
    }
    f[a][b] = min(f[a][b], dp(v, r, t));
    
    return f[a][b];
}


int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        int M;
        scanf("%d", &M);
        for (int j = 0; j < M; ++j) {
            char p[6], q[6];
            int r;
            scanf("%s%s%d", p, q, &r);
            x[i].push_back(node(r - 1, changeT(p), changeT(q)));
        }
        z[i] = vector<bool> (M, false);
        f[i] = vector<int> (M, 0);
    }
    
    dp(0, 0, 0);
    vector<pair<int, int> > ans;
    for (int i = 0; i < x[0].size(); ++i) {
        if (f[0][i] != INF) ans.push_back(make_pair(x[0][i].s, f[0][i]));
    }
    
    vector<pair<int, int> > temp;
    temp.push_back(ans[0]);
    for (int i = 1; i < ans.size(); ++i) {
        if (ans[i].first != ans[i-1].first) temp.push_back(ans[i]);
    }
    
    ans.clear();
    for (int i = 0; i < temp.size() - 1; ++i) {
        if (temp[i].second != temp[i+1].second) ans.push_back(temp[i]);
    }
    ans.push_back(temp[temp.size() - 1]);
    
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); ++i) 
        printf("%s %s\n", changeTB(ans[i].first).c_str(), changeTB(ans[i].second).c_str());
    
    return 0;
}
