#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAXN = 1001;
const double INFD = 1e10;
const double EPS = 1e-5;


struct node {
    double a, b, c;
    node(int _a, int _b, int _c) : a(_a), b(_b), c(_c){}
};

double A[MAXN][MAXN], B[MAXN][MAXN];


bool check(int N, double R) {
    vector<bool> z(N, false);
    vector<double> d(N, INFD);
    d[0] = 0;
    double ans = 0;
    for (int i = 0; i < N; ++i) {
        int a = -1;
        double b = INFD;
        for (int j = 0; j < N; ++j) {
            if (z[j] || d[j] >= b) continue;
            b = d[j];
            a = j;
        }
        z[a] = true;
        ans += b;
        for (int j = 0; j < N; ++j) d[j] = min(d[j], A[a][j] - R * B[a][j]);
    }
    return ans <= 0;
}


int main() {
    int N;
    while (cin >> N) {
        if (N == 0) break;
        vector<node> x;
        for (int i = 0; i < N; ++i) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            x.push_back(node(a, b, c));
        }
        
        double L = 0, R = 0;
        for (int i = 0; i < N; ++i)
         for (int j = 0; j < N; ++j) {
             A[i][j] = fabs(x[i].c - x[j].c);
             B[i][j] = sqrt((x[i].a - x[j].a) * (x[i].a - x[j].a)
                          + (x[i].b - x[j].b) * (x[i].b - x[j].b));
             R = max(R, A[i][j]);
         }
        
        if (check(N, L)) {
            cout << "0.000" << endl;
            continue;
        }
        
        while (L + EPS < R) {
            double mid = (L + R) / 2;
            if (check(N, mid)) R = mid; else L = mid;
        }
        printf("%.3lf\n", R);
    }
    
    return 0;
}
