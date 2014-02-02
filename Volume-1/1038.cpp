#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 150;
const int MAXS = 59049;
const int INF = 1000000000;


int N, M, K;
bool z[MAXN][10];
short f[MAXN][MAXS];
int MI[11];

int LEN(int S, int b) {
    return S / MI[b] % 3;
}

bool check2(int S, int a, int b) {
    if (b + 2 > M) return false;
    if (z[a][b] || z[a][b + 1]) return false;
    if (LEN(S, b) < 2 || LEN(S, b + 1) < 2) return false;
    return true;
}

bool check3(int S, int a, int b) {
    if (b + 3 > M) return false;
    if (z[a][b] || z[a][b + 1] || z[a][b + 2]) return false;
    if (LEN(S, b) < 1 || LEN(S, b + 1) < 1 || LEN(S, b + 2) < 1) return false;
    return true;
}

int makeS2(int SS, int b) {
    return SS | (1 << b) | (1 << (b + 1)); 
}

int makeS3(int SS, int b) {
    return SS | (1 << b) | (1 << (b + 1)) | (1 << (b + 2));
}

int makeS(int a, int S, int SS) {
    int temp = 0;
    for (int i = M - 1; i >= 0; --i) {
        temp *= 3;
        if (((SS & (1 << i)) == 0) && !z[a][i]) {
            if (LEN(S, i) >= 1) temp += 2; else temp += 1;
        }
    }
    return temp;
}

int dp(int a, int b, int S, int SS, int plus) {
    if (a < 0) return 0;
    if (b == 0 && f[a][S] >= 0) return f[a][S];
    if (b >= M) return plus + dp(a - 1, 0, makeS(a, S, SS), 0, 0);
    if (b == 0) f[a][S] = 0;
    int ans = 0;
    if (check2(S, a, b)) ans = max(ans, dp(a, b + 2, S, makeS2(SS, b), plus + 1));
    if (check3(S, a, b)) ans = max(ans, dp(a, b + 3, S, makeS3(SS, b), plus + 1));
    ans = max(ans, dp(a, b + 1, S, SS, plus));
    if (b == 0) f[a][S] = ans;
    return ans;
}


int main() {
    int times;
    cin >> times;
    MI[0] = 1;
    for (int i = 1; i < 11; ++i) MI[i] = MI[i - 1] * 3;
    
    while (times--) {
        cin >> N >> M >> K;
        memset(z, 0, sizeof(z));
        memset(f, 0xff, sizeof(f));
        for (int i = 0; i < K; ++i) {
            int a, b;
            cin >> a >> b;
            z[a - 1][b - 1] = true;
        }
        cout << dp(N - 1, 0, 0, 0, 0) << endl;
    }
    
    return 0;
}
