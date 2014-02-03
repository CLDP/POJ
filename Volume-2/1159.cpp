#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <cstdio>
#include <algorithm>
using namespace std;

string P;
int f[5001][3];



int main() {
    int N;
    cin >> N >> P;
    int T = 0;
    
    for (int i = 2; i <= N; ++i) {
        for (int j = 0; j < N + 1 - i; ++j) {
            if (P[j] == P[j + i - 1]) {
                f[j][T] = f[j + 1][(T + 1) % 3];
                continue;
            }
            f[j][T] = min(f[j][(T + 2) % 3] + 1, f[j + 1][(T + 2) % 3] + 1);
        }
        T = (T + 1) % 3;
    }
    
    T = (T + 2) % 3;
    cout << f[0][T] << endl;
    
    return 0;
}
