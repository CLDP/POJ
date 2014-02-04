#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

long long f[31][31];


int main() {
    for (int j = 0; j <= 30; ++j) f[1][j] = 1;
    for (int i = 2; i <= 30; ++i) {
        f[i][0] = i;
        for (int j = 1; j <= 30; ++j) f[i][j] = f[i-1][j-1] + 1 + f[i-1][j];
    }
    
    int N, M, times = 0;
    while (cin >> N >> M) {
        if (N == 0) break;
        ++times;
        cout << "Case " << times << ": " << f[N][M] << endl;
    }
    
    return 0;
}
