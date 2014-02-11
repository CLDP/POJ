#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAXN = 30010;
const int MAXM = 150010;
const int INF = 1000000000;

struct node {
    int a, b, c;
    bool operator < (node const &B) const {
        return a < B.a;
    }
};

int l[MAXN], r[MAXN], d[MAXN], stack[MAXN];
bool z[MAXN];
node y[MAXM];


int main() {
    int N, M;
    scanf("%d%d", &N, &M);
    for (int i = 0; i < M; ++i) scanf("%d%d%d", &y[i].a, &y[i].b, &y[i].c);
    sort(y, y + M);
    for (int i = 0; i < M; ) {
        int a = y[i].a, j = i;
        while (j < M && y[j].a == a) ++j;
        l[a] = i;
        r[a] = j;
        i = j;
    }
     
    for (int i = 1; i <= N; ++i) {
        d[i] = INF;
        z[i] = false;
    }
    d[1] = 0;
    z[1] = true;
    stack[0] = 1;
    int top = 1;
    while (top > 0) {
        int a = stack[--top];
        for (int i = l[a]; i < r[a]; ++i) {
            if (d[y[i].b] > d[a] + y[i].c) {
                d[y[i].b] = d[a] + y[i].c;
                if (!z[y[i].b]) {
                    z[y[i].b] = true;
                    stack[top++] = y[i].b;
                }
            }
        }
        z[a] = false;
    }
    cout << d[N] << endl;
    
    return 0;
}
