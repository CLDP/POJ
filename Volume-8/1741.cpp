#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;


const int MAXN = 10010;

int s[MAXN], K;
vector<pair<int, int> > x[MAXN];


int dfs(int a, int b) {
    s[a] = 1;
    for (int i = 0; i < x[a].size(); ++i) {
        if (x[a][i].first == b) continue;
        s[a] += dfs(x[a][i].first, a);
    }
    return s[a];
}


int find(int a, int f, int d, vector<int> &A) {
    A.push_back(d);
    for (int i = 0; i < x[a].size(); ++i) {
        if (x[a][i].first == f) continue;
        find(x[a][i].first, a, d + x[a][i].second, A);
    }
    return 0;
}

int calculate(vector<int> &A) {
    int N = A.size(), j = N - 1, ans = 0;
    for (int i = 0; i < N; ++i) {
        while (j >= 0 && A[i] + A[j] > K) --j;
        if (j == -1) break;
        ans += j + 1;
    }
    for (int i = 0; i < N; ++i)
     if (A[i] + A[i] <= K) --ans; else break;
    return ans / 2;
}


int deal(int a) {
    dfs(a, -1);
    if (s[a] == 1) return 0;
    
    int root = a, prev = -1;
    while (true) {
        bool flag = false;
        for (int i = 0; i < x[a].size(); ++i) {
            if (x[a][i].first == prev) continue;
            if (s[x[a][i].first] >= s[root] / 2) {
                flag = true;
                prev = a;
                a = x[a][i].first;
                break;
            }
        }
        if (!flag) break;
    }
    int ans = 0;
    vector<vector<int> > A(x[a].size());
    vector<int> B;
    for (int i = 0; i < x[a].size(); ++i) {
        find(x[a][i].first, a, x[a][i].second, A[i]);
        sort(A[i].begin(), A[i].end());
        for (int j = 0; j < A[i].size(); ++j) B.push_back(A[i][j]);
        ans -= calculate(A[i]);
    }
    sort(B.begin(), B.end());
    for (int i = 0; i < B.size(); ++i) 
     if (B[i] <= K) ++ans; else break;
    ans += calculate(B);
    for (int i = 0; i < x[a].size(); ++i) {
        int b = x[a][i].first;
        for (int j = 0; j < x[b].size(); ++j) 
         if (x[b][j].first == a) {
             x[b].erase(x[b].begin() + j);
             break;
         }
        ans += deal(b);
    }
    
    return ans;
}


int main() {
    int N;
    while (true) {
        scanf("%d%d", &N, &K);
        if (N == 0) break;
        int a, b, c;
        for (int i = 1; i <= N; ++i) x[i].clear();
        for (int i = 0; i < N - 1; ++i) {
            scanf("%d%d%d", &a, &b, &c);
            x[a].push_back(make_pair(b, c));
            x[b].push_back(make_pair(a, c));
        }
        cout << deal(1) << endl;
    }
    
    return 0;
}
