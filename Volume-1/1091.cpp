#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

long long N, M;
vector<int> fact;
long long ans;

long long pow(long long a, long long b) {
    long long ans = 1;
    while (b--) ans *= a;
    return ans;
}

int dfs(vector<long long> A, int num, int pos) {
    if (num == 0) {
        long long T = M;
        for (int i = 0; i < A.size(); ++i) T /= fact[A[i]];
        T = pow(T, N);
        if (A.size() % 2) ans -= T; else ans += T;
        return 0;
    }
    for (int i = pos; i < fact.size() - num + 1; ++i) {
        A[num - 1] = i;
        dfs(A, num - 1, i + 1);
    }
    return 0;
}


int main() {
    cin >> N >> M;
    long long T = sqrt((double)M), MM = M;
    for (int i = 2; i <= T; ++i) {
        if (M % i != 0) continue;
        while (M % i == 0) M /= i;
        fact.push_back(i);
    }
    
    if (M != 1) fact.push_back(M);
    
    M = MM;
    ans = pow(M, N);
    vector<long long> A;
    for (int i = 0; i < fact.size(); ++i) {
        A.push_back(0);
        dfs(A, i + 1, 0);
    }
    
    cout << ans << endl;
    return 0;
}
