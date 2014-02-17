#include <cstring>
#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 20010;


int x[MAXN], y[MAXN];


int main() {
    char type;
    int N;
    string P;
    cin >> type >> N >> P;
    if (type == 'B') {
        vector<int> A[26], B(26, 0), C[26];
        for (int i = 0; i < N; ++i) A[P[i] - 'a'].push_back(i);
        
        int M = 0;
        for (int i = 0; i < 26; ++i) {
            for (int j = 0; j < A[i].size(); ++j) C[i].push_back(M++);
            B[i] = A[i].size() - 1;
        }
         
        int t;
        cin >> t;
        --t;
        string ANS;
        for (int i = 0; i < N; ++i) {
            int temp = P[t] - 'a';
            if (i == 0) {
                ANS = P[C[temp][0]] + ANS;
                t = C[temp][0];
            } else {
                ANS = P[C[temp][B[temp]]] + ANS;
                t = C[temp][B[temp]--];
            }
        }
        cout << ANS << endl;
    } else {
        int M = 0, pos = 1;
        for (int j = 0; j < 26; ++j) 
         for (int i = 0; i < N; ++i) 
          if (P[i] == (char)(j + 'a')) {
              if (i == 0) cout << P[N - 1]; else cout << P[i - 1];
              ++M;
              if (i == 1) pos = M;
          }
        cout << endl;
        cout << pos << endl;
    }
    
    return 0;
}
