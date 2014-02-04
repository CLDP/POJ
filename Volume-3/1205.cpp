#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <cstdio>
#include <algorithm>
using namespace std;

const int MAXN = 101;

class HP {
public:
    int len, s[MAXN]; 
    HP() {
        s[len = 1] = 0;
    }
    HP(int a) {
        s[len = 1] = a;
    }             
    friend ostream &operator << (ostream &cout, const HP &x);
    HP operator + (const HP &b);
};


ostream &operator << (ostream &cout, const HP &x) {
    for (int i = x.len; i >= 1; --i) cout << x.s[i];
    return cout;
}


HP HP::operator + (const HP &b) {
    int i;
    HP c;
    c.s[1] = 0;
    for (i = 1; i <= len || i <= b.len || c.s[i]; ++i) {  
        if (i <= len) c.s[i] += s[i];                    
        if (i <= b.len) c.s[i] += b.s[i];        
        c.s[i+1] = c.s[i] / 10; 
        c.s[i] %= 10;
    }
    c.len = i-1;
    if (c.len == 0) c.len = 1;
    return c;
}


HP f[MAXN][2];


int main() {
    f[0][0] = 1;
    f[0][1] = 0;
    for (int i = 1; i < 100; ++i) {
        f[i][0] = f[i-1][0] + f[i-1][0] + f[i-1][1];
        f[i][1] = f[i-1][0] + f[i-1][1];
    }
    
    int M;
    while (cin >> M) {
        cout << f[M - 1][0] + f[M - 1][1] << endl;
    }
    
    return 0;
}
