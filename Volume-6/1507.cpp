#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 1050000;

int x[MAXN];

int insert(int a) {
    for (int i = a; i < MAXN; i += (i & -i)) ++x[i];
    return 0;
}

int query(int a) {
    int ans = 0;
    for (int i = a; i > 0; i -= (i & -i)) ans += x[i];
    return ans;
}


int main() {
    int times;
    cin >> times;
    while (times--) {
        int N, a, M;
        cin >> N;
        memset(x, 0, sizeof(x));
        long long ans = 0;
        M = N * N * N;
        for (int i = 0; i < M; ++i) {
            cin >> a;
            if (a == 0) {
                ans += 3 * N - 3 - i / (N * N) - i / N % N - i % N;
                ans += query(MAXN - 1) - query(M);
                insert(M);
            } else {
                ans += query(MAXN - 1) - query(a);
                insert(a);
            }
        }
        if (ans % 2 == 0) 
            cout << "Puzzle can be solved." << endl; 
        else 
            cout << "Puzzle is unsolvable." << endl;
    }
    return 0;
}
