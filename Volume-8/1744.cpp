#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;


const int MAXN = 30010;

int N;
int x[MAXN];

bool check(int a) {
    int i = 0;
    while (i < N && (x[i] - 1) * 20 <= a) ++i;
    int time = (x[i] - 1) * 4, prev = x[i];
    while (true) {
        while (time + 4 + (prev + 1 - x[i]) * 20 <= a) {
            time += 4;
            ++prev;
        }
        while (i < N && abs(prev - x[i]) * 20 + time <= a) ++i;
        if (i == N) break;
        time += 10;
        time += (x[i] - prev) * 4;
        prev = x[i];
        if (time > a) break;
    }
    return time <= a;
}


int main() {
    while (true) {
        scanf("%d", &N);
        if (N == 0) break;
        for (int i = 0; i < N; ++i) scanf("%d", &x[i]);
        int L = 0, R = x[N - 1] * 20;
        while (L + 1 < R) {
            int mid = (L + R) >> 1;
            if (check(mid)) R = mid; else L = mid;
        }
        printf("%d\n", R);
    }
    
    return 0;
}
