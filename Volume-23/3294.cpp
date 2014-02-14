#include <algorithm>
#include <numeric>
#include <cstring>
#include <cstdio>
#include <string>
#include <vector>
#include <set>
#include <iostream>
const int MAX_LEN = 110000;
using namespace std;


struct SuffixArray {
    int n;
    int m[2][MAX_LEN];
    // sa[0..n] = (0..n) saves which suffix is rank i
    // rank[0..n-1] = (1..n) saves this suffix's rank, start from 1
    // height[i (1..n)] is the longest prefix of sa[i-1], sa[i]
    int sa[MAX_LEN], rank[MAX_LEN], height[MAX_LEN];

    void indexSort(int sa[], int ord[], int id[], int nId) { 
        //ord is the ordering get from prev stage
        static int cnt[MAX_LEN];
        memset(cnt, 0, sizeof(0) * nId);

        for (int i = 0; i < n; ++i) ++cnt[id[i]];
        partial_sum(cnt, cnt + nId, cnt);
        for (int i = n - 1; i >= 0; --i) sa[--cnt[id[ord[i]]]] = ord[i];
    }
    
    void calheight(int *r, int *sa, int n) {
         int i, j, k = 0;
         for (i = 1; i <= n; i++) rank[sa[i - 1]] = i - 1;
         for (i = 0; i < n; height[rank[i++]] = k)
          for (k ? k-- : 0, j = sa[rank[i] - 1]; r[i + k] == r[j + k]; k++);
    }

    int *id, *oId;
    void init(int s[], int _n) { //s[n] == 0
        n = _n;
        static int w[MAX_LEN];
        memcpy(w, s, sizeof(int) * n);
        sort(w, w + n);
        int nId = unique(w, w + n) - w;
        id = m[0], oId = m[1];
        for (int i = 0; i < n; ++i) {
            id[i] = lower_bound(w, w + nId, s[i]) - w;
        }
        static int ord[MAX_LEN];
        for (int i = 0; i < n; ++i) ord[i] = i;
        indexSort(sa, ord, id, nId);
        for (int k = 1; k <= n && nId < n; k <<= 1) {
            //get the prev order
            // k -> k*2
            int cur = 0;
            for (int i = n - k; i < n; ++i) ord[cur++] = i;
            for (int i = 0; i < n; ++i) {
                if (sa[i] >= k) ord[cur++] = sa[i] - k;
            }
            indexSort(sa, ord, id, nId);
            //get new id
            cur = 0;
            swap(oId, id);
            for (int i = 0; i < n; ++i) {
                int c = sa[i], p = i ? sa[i - 1] : 0;
                id[c] = (i == 0 || oId[c] != oId[p] || oId[c + k] != oId[p + k]) ? cur++ : cur - 1;
            }
            nId = cur;
        }
        calheight(s, sa, n);
    }
    
} sa;


int x[MAX_LEN], belong[MAX_LEN];
char y[MAX_LEN];


int main() {
    int K, times = 0;
    while (cin >> K) {
        if (K == 0) break;
        if (times++) printf("\n");
        int N = 0;
        for (int i = 0; i < K; ++i) {
            scanf("%s", y);
            int M = strlen(y);
            for (int j = 0; j < M; ++j) {
                x[N + j] = y[j] - 'a' + 200;
                belong[N + j] = i;
            }
            x[N + M] = i;
            N += M + 1;
        }
        sa.init(x, N);
        
        int L = 0, R = 1010;
        set<int> C;
        while (L + 1 < R) {
            int mid = (L + R) >> 1;
            bool flag = false;
            for (int i = K; i < N; ++i) {
                if (sa.height[i] < mid) {
                    C.clear();
                    continue;
                }
                C.insert(belong[sa.sa[i - 1]]);
                C.insert(belong[sa.sa[i]]);
                if (C.size() > K / 2) {
                    flag = true;
                    break;
                }
            }
            if (flag) L = mid; else R = mid;
        }
        
        if (L == 0) {
            printf("?\n");
            continue;
        }
        
        vector<int> ansT;
        for (int i = K; i < N; ++i) {
            if (sa.height[i] < L) {
                C.clear();
                continue;
            }
            C.insert(belong[sa.sa[i - 1]]);
            C.insert(belong[sa.sa[i]]);
            if (C.size() > K / 2) ansT.push_back(i);
        }
        sort(ansT.begin(), ansT.end());
        
        for (int i = 0; i < ansT.size(); ++i) {
            if (i > 0 && ansT[i] == ansT[i-1] + 1 && sa.height[ansT[i]] >= L) continue;
            for (int j = sa.sa[ansT[i]]; j < sa.sa[ansT[i]] + L; ++j) printf("%c", (char)(x[j] - 200 + 'a'));
            printf("\n");
        }
    }
    
    return 0;
}
