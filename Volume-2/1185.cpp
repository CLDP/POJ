#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

const int MAXN = 102;
const int MAXS = 61;


int N, M;
string x[MAXN];
vector<int> S[MAXN];
vector<int> T[MAXN];
int f[MAXN][MAXS][MAXS];

int dfs(int a, int b, string P, int SS, int TT) {
    if (a >= P.size()) {
        S[b].push_back(SS);
        T[b].push_back(TT);
        return 0;
    }
    dfs(a + 1, b, P, SS, TT);
    if (P[a] == 'P') dfs(a + 3, b, P, SS + (1 << a), TT + 1);
    return 0;
}

bool check(int S0, int S1, int S2) {
    for (int i = 0; i < M; ++i) {
        int temp = ((S0 >> i) & 1) + ((S1 >> i) & 1) + ((S2 >> i) & 1);
        if (temp > 1) return false;
    }
    return true;
}

int main() {
    cin >> N >> M;
    for (int i = 2; i <= N + 1; ++i) {
        cin >> x[i];
        dfs(0, i, x[i], 0, 0);
    }
    
    int ans = 0;
    S[0].push_back(0);
    S[1].push_back(0);
    for (int i = 2; i <= N + 1; ++i) {
        for (int j = 0; j < S[i].size(); ++j) 
         for (int k1 = 0; k1 < S[i-2].size(); ++k1)
          for (int k2 = 0; k2 < S[i-1].size(); ++k2) 
           if (check(S[i-2][k1], S[i-1][k2], S[i][j])) {
               f[i][j][k2] = max(f[i][j][k2], f[i-1][k2][k1] + T[i][j]);
               ans = max(ans, f[i][j][k2]);
           }
    }
    
    cout << ans << endl;
    
    return 0;
}
