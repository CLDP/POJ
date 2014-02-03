#include <vector>
#include <string>
#include <queue>
#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

const int MI[6] = {1, 10, 100, 1000, 10000, 100000};


struct node {
    int a, b, c;
    
    node(int A, int B, int C): a(A), b(B), c(C) {}
};


int LtoC[6][6][6][6][6][6];
vector<int> CtoL[720];
int f[720][64][6];

int calculate(int a, int b, int A, int B) {
    vector<int> AA, BB;
    vector<int> C = CtoL[a];
    int ans = 0;
    for (int i = 0; i < 6; ++i) {
        BB.push_back(B / MI[i] % 10);
        AA.push_back(A / MI[C[i]] % 10);
        ans += abs(AA[i] - BB[i]);
        if ((b & (1 << i)) == 0 && AA[i] != BB[i]) ans += 1000;
    }
    return ans;
}


int main() {
    vector<int> S;
    for (int i = 0; i < 6; ++i) S.push_back(i);
    for (int i = 0; i < 720; ++i) {
        LtoC[S[0]][S[1]][S[2]][S[3]][S[4]][S[5]] = i;
        CtoL[i] = S;
        next_permutation(S.begin(), S.end());
    }
    
    queue<node> que;
    que.push(node(0, 1 << 5, 5));
    f[0][1 << 5][5] = 1;
    while (!que.empty()) {
        node P = que.front();
        que.pop();
        
        if (P.c < 5 && f[P.a][P.b][P.c + 1] == 0) {
            f[P.a][P.b][P.c + 1] = f[P.a][P.b][P.c] + 1;
            que.push(node(P.a, P.b, P.c + 1));
        }
        
        if (P.c > 0) {
            if (f[P.a][P.b | (1 << (P.c - 1))][P.c - 1] == 0) {
                f[P.a][P.b | (1 << (P.c - 1))][P.c - 1] = f[P.a][P.b][P.c] + 1;
                que.push(node(P.a, P.b | (1 << (P.c - 1)), P.c - 1));
            }
        }
        
        if (P.c < 5) {
            vector<int> &C = CtoL[P.a];
            swap(C[P.c], C[5]);
            int tC = LtoC[C[0]][C[1]][C[2]][C[3]][C[4]][C[5]];
            if (f[tC][P.b][P.c] == 0) {
                f[tC][P.b][P.c] = f[P.a][P.b][P.c] + 1;
                que.push(node(tC, P.b, P.c));
            }
            swap(C[P.c], C[5]);
        }
        
        if (P.c > 0) {
            vector<int> &C = CtoL[P.a];
            swap(C[P.c], C[0]);
            int tC = LtoC[C[0]][C[1]][C[2]][C[3]][C[4]][C[5]];
            if (f[tC][P.b | 1][P.c] == 0) {
                f[tC][P.b | 1][P.c] = f[P.a][P.b][P.c] + 1;
                que.push(node(tC, P.b | 1, P.c));
            }
            swap(C[P.c], C[0]);
        }
    }
    
    int A, B, ans = 1000;
    cin >> A >> B;
    
    int l[10] = {32, 48, 56, 60, 62, 63, 33, 49, 57, 61};
    
    for (int i = 0; i < 720; ++i)
     for (int j = 0; j < 10; ++j)
      for (int k = 0; k < 6; ++k)
       if (f[i][l[j]][k] > 0) ans = min(ans, f[i][l[j]][k] + calculate(i, l[j], A, B));
    
    cout << ans - 1 << endl;
    
    return 0;
}
