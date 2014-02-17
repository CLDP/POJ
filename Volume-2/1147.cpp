#include <cstring>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 3010;

int x[MAXN], y[MAXN];


int main() {
    int N;
    cin >> N;
    vector<int> A, B;
    for (int i = 0; i < N; ++i) {
        cin >> x[i];
        if (x[i] == 0) A.push_back(i); else B.push_back(i);
    }
    
    int M = 0;
    for (int i = 0; i < A.size(); ++i) y[M++] = A[i];
    for (int i = 0; i < B.size(); ++i) y[M++] = B[i];
    
    int t = 0;
    for (int i = 0; i < N; ++i) {
        t = y[t];
        cout << x[t];
        if (i != N - 1) cout << " "; else cout << endl;
    }
    
    return 0;
}
