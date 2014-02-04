#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXN = 302;
const int MAXL = 52;
const int KM = 10000;

class HP {
public:
    int s[MAXL + 1], len;
    
    HP() {
        memset(s, 0, sizeof(s));
        len = 1;
    }
    HP(int a) {
        memset(s, 0, sizeof(s));
        if (a > 0) {
            s[MAXL] = a;
            len = MAXL;
        } else {
            len = 1;
        }
    }
    HP operator + (const HP &b);
    HP operator / (const int &b);
    friend ostream &operator << (ostream &cout, const HP &x);
};

HP HP::operator + (const HP &b) {
    int i;
    HP c;
    c.s[1] = 0;
    for (i = 1; i <= len || i <= b.len || c.s[i]; ++i) {  
        if (i <= len) c.s[i] += s[i];                    
        if (i <= b.len) c.s[i] += b.s[i];        
        c.s[i+1] = c.s[i] / KM; 
        c.s[i] %= KM;
    }
    c.len = i-1;
    if (c.len == 0) c.len = 1;
    return c;
}

HP HP::operator / (const int &b) {
    // b is always 2
    for (int i = len; i > 0; --i) {
        s[i-1] += (s[i] % 2) * KM;
        s[i] /= 2;
    }
    while (len > 1 && s[len] == 0) --len;
    return (*this);
}

ostream &operator << (ostream &cout, const HP &x) {
    if (x.len == 1 && x.s[1] == 0) {
        cout << 0;
        return cout;
    }
    int minP = 1;
    while (minP <= MAXL && x.s[minP] == 0) ++minP;
    if (minP == MAXL) {
        cout << x.s[MAXL];
        return cout;
    }
    cout << x.s[MAXL] << ".";
    for (int i = MAXL - 1; i >= minP; --i) {
        string P;
        if (i == minP) {
            if (x.s[i] % 10 > 0 || P != "") P = (char)(x.s[i] % 10 + '0') + P;
            if (x.s[i] / 10 % 10 > 0 || P != "") P = (char)(x.s[i] / 10 % 10 + '0') + P;
            if (x.s[i] / 100 % 10 > 0 || P != "") P = (char)(x.s[i] / 100 % 10 + '0') + P;
            if (x.s[i] / 1000 % 10 > 0 || P != "") P = (char)(x.s[i] / 1000 % 10 + '0') + P;
        } else {
            cout << x.s[i] / 1000 % 10 << x.s[i] / 100 % 10 << x.s[i] / 10 % 10 << x.s[i] % 10;
        }
        cout << P;
    }
    return cout;
}


vector<int> x[MAXN];
pair<int, int> f[MAXN];
int y[MAXN];
bool z[MAXN];
HP g[MAXN][MAXN];


int main() {
    int N, M;
    cin >> N >> M;
    for (int i = 0; i < M; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        x[b].push_back(a);
        x[c].push_back(a);
        f[a] = make_pair(b, c);
        y[a] += 2;
    }
    
    queue<int> que;
    for (int i = 1; i <= N; ++i) {
        if (y[i] != 0) continue;
        que.push(i);
    }
    
    while (!que.empty()) {
        int a = que.front();
        que.pop();
        z[a] = true;
        g[a][a] = 100;
        if (f[a].first == 0) {
            for (int i = 1; i <= N; ++i) {
                if (a == i) continue;
                g[a][i] = g[i][a] = 0;
            }
        } else {
            for (int i = 1; i <= N; ++i) {
                if (a == i) continue;
                g[a][i] = g[i][a] = (g[f[a].first][i] + g[f[a].second][i]) / 2;
            }
        }
        
        for (int j = 0; j < x[a].size(); ++j) {
            --y[x[a][j]];
            if (y[x[a][j]] == 0) que.push(x[a][j]);
        }
    }
    cin >> M;
    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        cout << g[a][b] << "%" << endl;
    }
    
    return 0;
}
