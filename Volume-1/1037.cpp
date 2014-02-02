#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 21;

long long f[MAXN][MAXN][2];


int main() {
    int times;
    cin >> times;
    
    f[1][0][0] = f[1][0][1] = 1;
    for (int i = 2; i < MAXN; ++i) {
        f[i][0][0] = 0;
        for (int j = 1; j < i; ++j) f[i][j][0] = f[i][j-1][0] + f[i-1][j-1][1];
        f[i][i-1][1] = 0;
        for (int j = i - 2; j >= 0; --j) f[i][j][1] = f[i][j+1][1] + f[i-1][j][0];
    }
    
    while (times--) {
        int N;
        long long K;
        cin >> N >> K;
        if (N == 1) {
            cout << 1 << endl;
            continue;
        }
        
        vector<int> ans;
        int j;
        for (j = 0; f[N][j][0] + f[N][j][1] < K; ++j) K -= f[N][j][0] + f[N][j][1];
        ans.push_back(j);
        for (j = 0; j < ans[0] && f[N-1][j][1] < K; ++j) K -= f[N-1][j][1];
        if (j == ans[0]) {
            for ( ; f[N-1][j][0] < K; ++j) K -= f[N-1][j][0];
        }
        ans.push_back(j);
        
        for (int i = 2; i < N; ++i) {
            if (ans[i-2] > ans[i-1]) {
                for (j = ans[i-1]; f[N-i][j][0] < K; ++j) K -= f[N-i][j][0];
            } else {
                for (j = 0; f[N-i][j][1] < K; ++j) K -= f[N-i][j][1];
            }
            ans.push_back(j);
        }
        
        vector<bool> C(N, true);
        for (int i = 0; i < N; ++i) {
            ++ans[i];
            j = 0;
            while (true) {
                if (C[j]) --ans[i];
                if (ans[i] == 0) break;
                ++j;
            }
            C[j] = false;
            ans[i] = j + 1;
        }
        
        for (int i = 0; i < N - 1; ++i) cout << ans[i] << " "; 
        cout << ans[N - 1] << endl;
    }
    return 0;
}
