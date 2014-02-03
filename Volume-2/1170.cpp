#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <cstdio>
#include <map>
#include <algorithm>
using namespace std;

const int MI[5] = {1, 6, 36, 216, 1296};
const int INF = 1000000000;

struct node {
    int n, price;
    vector<int> x, y;
};

int N, M;
map<int, int> C;
int f[10000];
int K[5], P[5];
vector<node> order;

vector<int> changeA(int a) {
    vector<int> num;
    for (int i = 0; i < N; ++i) {
        num.push_back(a % 6);
        a /= 6;
    }
    return num;
}

int changeB(vector<int> &A) {
    int ans = 0;
    for (int i = 0; i < N; ++i) ans += A[i] * MI[i];
    return ans;
}

int DP(int a) {
    if (f[a] > 0) return f[a];
    if (a == 0) return 0;
    f[a] = INF;
    vector<int> num = changeA(a);
    for (int i = 0; i < N; ++i) {
        if (num[i] == 0) continue;
        --num[i];
        f[a] = min(f[a], DP(changeB(num)) + P[i]);
        ++num[i];
    }
    for (int i = 0; i < M; ++i) {
        bool flag = true;
        for (int j = 0; j < order[i].n; ++j) flag &= (num[C[order[i].x[j]]] >= order[i].y[j]);
        if (!flag) continue;
        for (int j = 0; j < order[i].n; ++j) num[C[order[i].x[j]]] -= order[i].y[j];
        f[a] = min(f[a], DP(changeB(num)) + order[i].price);
        for (int j = 0; j < order[i].n; ++j) num[C[order[i].x[j]]] += order[i].y[j];
    }
    return f[a];
}

int main() {
    cin >> N;
    for (int i = 0; i < N; ++i) {
        int a;
        cin >> a >> K[i] >> P[i];
        C[a] = i;
    }
    cin >> M;
    for (int i = 0; i < M; ++i) {
        node O;
        cin >> O.n;
        for (int j = 0; j < O.n; ++j) {
            int a, b;
            cin >> a >> b;
            O.x.push_back(a);
            O.y.push_back(b);
        }
        cin >> O.price;
        order.push_back(O);
    }
    
    int temp = 0;
    for (int i = 0; i < N; ++i) temp += MI[i] * K[i];
    cout << DP(temp) << endl;
    
    return 0;
}
