#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 21;

int f[1 << 12];
int C[12];
int z[18];

int decode(int a, int b) {
    if (a == 1 && b == 2) return 0;
    if (a == 2 && b == 3) return 1;
    if (a == 1 && b == 3) return 2;
    if (a == 2 && b == 4) return 3;
    if (a == 4 && b == 5) return 4;
    if (a == 2 && b == 5) return 5;
    if (a == 3 && b == 5) return 6;
    if (a == 5 && b == 6) return 7;
    if (a == 3 && b == 6) return 8;
    if (a == 4 && b == 7) return 9;
    if (a == 7 && b == 8) return 10;
    if (a == 4 && b == 8) return 11;
    if (a == 5 && b == 8) return 12;
    if (a == 8 && b == 9) return 13;
    if (a == 5 && b == 9) return 14;
    if (a == 6 && b == 9) return 15;
    if (a == 9 && b == 10) return 16;
    if (a == 6 && b == 10) return 17;
    return -1;
}

int check(int a) {
    if (a == 0) return (z[1] && z[2]);
    if (a == 1) return (z[0] && z[2]) + (z[5] && z[6]);
    if (a == 2) return (z[0] && z[1]);
    if (a == 3) return (z[4] && z[5]);
    if (a == 4) return (z[3] && z[5]) + (z[11] && z[12]);
    if (a == 5) return (z[3] && z[4]) + (z[1] && z[6]);
    if (a == 6) return (z[1] && z[5]) + (z[7] && z[8]);
    if (a == 7) return (z[6] && z[8]) + (z[14] && z[15]);
    if (a == 8) return (z[6] && z[7]);
    if (a == 9) return (z[10] && z[11]);
    if (a == 10) return (z[9] && z[11]);
    if (a == 11) return (z[9] && z[10]) + (z[4] && z[12]);
    if (a == 12) return (z[4] && z[11]) + (z[13] && z[14]);
    if (a == 13) return (z[12] && z[14]);
    if (a == 14) return (z[12] && z[13]) + (z[7] && z[15]);
    if (a == 15) return (z[7] && z[14]) + (z[16] && z[17]);
    if (a == 16) return (z[15] && z[17]);
    if (a == 17) return (z[15] && z[16]);
}


int dp(int S, int N, int left, bool player) {
    if (S == (1 << N) - 1) return 0;
    if (f[S] > 0) return f[S];
    int ans = 0;
    for (int i = 0; i < N; ++i) {
        if (S & (1 << i)) continue;
        int CC = check(C[i]);
        z[C[i]] = true;
        if (CC > 0) {
            ans = max(ans, dp(S | (1 << i), N, left - CC, player) + CC);
        } else {
            ans = max(ans, left - dp(S | (1 << i), N, left, !player));
        }
        z[C[i]] = false;
    }
    return f[S] = ans;
}

int main() {
    int times;
    cin >> times;
    for (int TT = 0; TT < times; ++TT) {
        bool player = false; // A is false
        int N;
        cin >> N;
        memset(z, 0, sizeof(z));
        memset(f, 0, sizeof(f));
        
        int ans[2] = {0, 0};
        for (int i = 0; i < N; ++i) {
           int a, b;
           cin >> a >> b;
           if (a > b) swap(a, b);
           z[decode(a, b)] = true;
           if (check(decode(a, b)) > 0) ans[player] += check(decode(a, b)); else player = !player;
        }
        
        for (int i = 0, j = 0; i < 18; ++i) {
            if (z[i]) continue;
            C[j++] = i;
        }
        
        int left = 9 - ans[0] - ans[1];
        dp(0, 18 - N, left, player);
        if (!player) {
            ans[0] += f[0];
            ans[1] += left - f[0];
        } else {
            ans[0] += left - f[0];
            ans[1] += f[0];
        }
        
        cout << "Game " << TT + 1 << ": " << (ans[0] > ans[1] ? "A" : "B") << " wins." << endl;
    }
    return 0;
}
