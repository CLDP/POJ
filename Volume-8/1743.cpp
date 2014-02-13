#include <algorithm>
#include <numeric>
#include <cstring>
#include <cstdio>
#include <string>
#include <iostream>
const int MAX_LEN = 21000;
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


int x[MAX_LEN];



int main() {
    int N;
    while (cin >> N) {
        if (N == 0) break;
        scanf("%d", &x[0]);
        int temp = x[0], temp2;
        for (int i = 1; i < N; ++i) {
            scanf("%d", &temp2);
            x[i - 1] = temp2 - temp + 100;
            temp = temp2;
        }
        --N;
        x[N] = 0;
        if (N == 0) {
            cout << 0 << endl;
            continue;
        }
        sa.init(x, N + 1);
        int L = 0, R = N + 1;
        while (L + 1 < R) {
            int mid = (L + R) >> 1;
            int minS = sa.sa[0], maxS = sa.sa[0];
            bool flag = false;
            for (int i = 1; i <= N; ++i) {
                if (sa.height[i] >= mid) {
                    minS = min(minS, sa.sa[i]);
                    maxS = max(maxS, sa.sa[i]);
                    if (maxS - minS > mid) {
                        flag = true;
                        break;
                    }
                } else {
                    minS = maxS = sa.sa[i];
                }
            }
            if (flag) L = mid; else R = mid;
        }
        ++L;
        if (L < 5) L = 0;
        cout << L << endl;
    }
    
    return 0;
}
