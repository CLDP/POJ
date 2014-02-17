#include <cstdio>
#include <vector>
#include <cmath>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 100010;

int x[MAXN];
long long s[MAXN], qx[MAXN], qy[MAXN];


int main() {
    int N, M;
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; ++i) {
        scanf("%d", &x[i]);
        s[i] = s[i - 1] + x[i];
    }
    
    int l = 0, r = 1;
    qx[0] = 0, qy[0] = s[0];
    int ans = 0;
    for (int i = M; i <= N; ++i) {
        while (l + 1 < r && (s[i] - qy[l + 1]) * (i - qx[l]) >= (s[i] - qy[l]) * (i - qx[l + 1])) ++l;
        int temp = (s[i] - qy[l]) * 1000 / (i - qx[l]);
        if (temp > ans) ans = temp;
        while (l + 1 < r && (s[i - M + 1] - qy[r - 1]) * (qx[r - 1] - qx[r - 2]) 
                         <= (qy[r - 1] - qy[r - 2]) * (i - M + 1 - qx[r - 1])) --r;
        qx[r] = i - M + 1, qy[r] = s[i - M + 1];
        ++r;
    }
    
    cout << ans << endl;
    
    return 0;
}
