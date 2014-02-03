#include <cstring>
#include <iostream>
using namespace std;

int x[30], y[30];
int l[6];
int f[6][6][6][6][6];

int dp(int a) {
    if (f[l[1]][l[2]][l[3]][l[4]][l[5]] != 0) return f[l[1]][l[2]][l[3]][l[4]][l[5]];
    int now = 0;
    if (x[a] > 0) {
        if (l[x[a]] + 1 == y[a] && l[x[a]] < l[x[a]-1]) {
            ++l[x[a]];
            now += dp(a+1);
            --l[x[a]];
        }
    } else {
        for (int i = 1; i <= 5; ++i)
         if (l[i] < l[i-1]) {
             ++l[i];
             now += dp(a+1);
             --l[i];
         }
    }
    f[l[1]][l[2]][l[3]][l[4]][l[5]] = now;
    return now;
}



int main() {
    char p;
    cin >> p;
    if (p == 'N') {
        int n;
        cin >> n;
        for (int i = 1; i <= 5; ++i)
         for (int j = 1; j <= 5; ++j)
          for (int k = 1; k <= 25; ++k)
           if (x[k] == 0) {
               x[k] = i;
               y[k] = j;
               memset(f, 0, sizeof(f));
               f[5][5][5][5][5] = 1;
               memset(l, 0, sizeof(l));
               l[0] = 5;
               int m = dp(1);
               if (m < n)
                   n -= m;
               else
                   break;
               x[k] = 0;
           }
        
        int z[6][6];
        for (int i = 1; i <= 25; ++i) z[x[i]][y[i]] = i;
        
        for (int i = 1; i <= 5; ++i)
         for (int j = 1; j <= 5; ++j) cout << char(z[i][j] + 'A' - 1);
         
        cout << endl;
    } else {
        int z[6][6];
        for (int i = 1; i <= 5; ++i)
         for (int j = 1; j <= 5; ++j) {
             char q;
             cin >> q;
             z[i][j] = q - 'A' + 1;
         }
        
        int n = 1;
        
        for (int i = 1; i <= 5; ++i)
         for (int j = 1; j <= 5; ++j) {
             for (int k = 1; k < z[i][j]; ++k)
              if (x[k] == 0) {
                  x[k] = i;
                  y[k] = j;
                  memset(f, 0, sizeof(f));
                  f[5][5][5][5][5] = 1;
                  memset(l, 0, sizeof(l));
                  l[0] = 5;
                  int m = dp(1);
                  n += m;
                  x[k] = 0;
              }
             
             x[z[i][j]] = i;
             y[z[i][j]] = j;
         }
        
        cout << n << endl;
    
    }
    
    return 0;
}
