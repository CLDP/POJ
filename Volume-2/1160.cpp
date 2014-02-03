#include <vector>
#include <iostream>
using namespace std;

const int MAXN = 301;
const int MAXM = 31;
const int INF = 1000000000;

int f[MAXN][MAXM];


int main() {
    int N, M;
    cin >> N >> M;
    vector<int> x(N + 1, 0);
    for (int i = 1; i <= N; ++i) cin >> x[i];
    
    for (int i = 1; i <= N; ++i) {
        for (int j = 0; j <= min(i, M); ++j) {
            f[i][j] = INF;
            if (j == 0) continue;
            int sumA = 0, sumB = 0;
            for (int k = i; k >= j - 1; --k) {
                f[i][j] = min(f[i][j], f[k][j-1] + sumA - sumB);
                
                sumB += x[k];
                if ((i - k) % 2 == 1) {
                    sumA += x[i - (i - k) / 2];
                } else {
                    sumB -= x[i - (i - k) / 2];
                }
                
            }
        }
    }
    
    cout << f[N][M] << endl;
    
    return 0;
}
