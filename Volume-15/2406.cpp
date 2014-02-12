#include <cstring>
#include <cstdio>
const int MAX_LEN = 1000100;

char y[MAX_LEN];
int N, next[MAX_LEN];

int Get_Next() {
    int j = 0, k = -1;
    next[0] = -1;
    while (j < N) 
     if (k == -1 || y[j] == y[k]) {
         next[++j] = ++k;
     } else k = next[k];
    return 0;
}

int main() {
    while (true) {
        scanf("%s", y);
        N = strlen(y);
        if (N == 1 && y[0] == '.') break;
        Get_Next();
        printf("%d\n", (N % (N - next[N]) == 0) ? N / (N - next[N]) : 1);
    }
    return 0;
}
