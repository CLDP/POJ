#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 702;

int x[MAXN][MAXN];
int minP[MAXN], maxP[MAXN];
int P1[MAXN], P2[MAXN];

int main() {
    int N, M, K;
    
    cin >> M >> N >> K;
    for (int i = 0; i < N; ++i) 
     for (int j = 0; j < M; ++j) cin >> x[i][j];
    
    int ans = 0;
    for (int j = 0; j < M; ++j) {
        vector<int> minL(N, 0), maxL(N, 0);
        for (int i = 0; i < N; ++i) minL[i] = maxL[i] = x[i][j];
        for (int l = 1; l <= 100; ++l) {
            int upmost = -1, l1 = 0, r1 = -1, l2 = 0, r2 = -1;
            for (int i = 0; i < N; ++i) {
                while (l1 <= r1 && minP[r1] > minL[i]) --r1;
                minP[++r1] = minL[i];
                P1[r1] = i;
                while (l2 <= r2 && maxP[r2] < maxL[i]) --r2;
                maxP[++r2] = maxL[i];
                P2[r2] = i;
                
                while (l1 <= r1 && maxL[i] - minP[l1] > K) {
                    upmost = max(upmost, P1[l1]);
                    ++l1;
                }
                
                while (l2 <= r2 && maxP[l2] - minL[i] > K) {
                    upmost = max(upmost, P2[l2]);
                    ++l2;
                }
                
                ans = max(ans, (i - upmost) * l);
            
                minL[i] = min(minL[i], x[i][j + l]);
                maxL[i] = max(maxL[i], x[i][j + l]);
            }
            if (j + l >= M) break;
        }
    }
    
    cout << ans << endl;
    
    return 0;
}
