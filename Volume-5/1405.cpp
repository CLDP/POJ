#include <iostream>
#include <cstdio>
using namespace std;

const int MAXL = 20010; 
const int km = 10000;

class HP {
    public:
        int len;
        long long s[MAXL];
        HP() {(*this) = 0;};                  
        HP(int inte) {(*this) = inte;};   
        friend ostream &operator << (ostream &cout, const HP &x);
        HP operator = (int inte);
        HP operator * (const HP &b);
        HP operator + (const HP &b);
        int Compare(const HP &b);
};

ostream &operator << (ostream &cout, const HP &x) {
    printf("%d",x.s[x.len]);
    for (int i = x.len-1; i >= 1; --i) {
        printf("%d",x.s[i] / 1000);
        printf("%d",x.s[i] / 100 % 10);
        printf("%d",x.s[i] / 10 % 10);
        printf("%d",x.s[i] % 10);
    }
    return cout;
}


HP HP::operator = (int inte) {
    if (inte == 0) {
        len = 1;
        s[1] = 0;
        return (*this);
    }
    len = 0;
    while (inte > 0) {
        s[++len] = inte % km;
        inte /= km;
    }
    return (*this);
}

HP HP::operator * (const HP &b) {
    int i, j;
    HP c;
    c.len = len + b.len;
    for (i = 1; i <= c.len; ++i) c.s[i] = 0;
    for (i = 1; i <= len; ++i) 
     for (j = 1; j <= b.len; ++j) 
      c.s[i+j-1] += s[i]*b.s[j];
    
    //Warning: As we only do this once, the number may be bigger than int!!
    //Warning: If MAXL > 1000, it is very easy to be error!!!
    for (i = 1; i < c.len; ++i) {
        c.s[i+1] += c.s[i] / km;
        c.s[i] %= km;
    }
    while (c.s[i]) {
        c.s[i+1] = c.s[i] / km;
        c.s[i] %= km; 
        ++i;
    }
    while (i > 1 && !c.s[i]) i--;
    c.len = i;
    return c;
}

HP HP::operator + (const HP &b) {
    int i;
    HP c;
    c.s[1] = 0;
    for (i = 1; i <= len || i <= b.len || c.s[i]; ++i) {  
        if (i <= len) c.s[i] += s[i];                    
        if (i <= b.len) c.s[i] += b.s[i];        
        c.s[i+1] = c.s[i] / km; 
        c.s[i] %= km;
    }
    c.len = i-1;
    if (c.len == 0) c.len = 1;
    return c;
}


int main() {
    int N;
    cin >> N;
    if (N == 1) {
        cout << 2 << endl;
        return 0;
    }
    if (N == 2) {
        cout << 2 << endl << 3 << endl;
        return 0;
    }
    HP C[2];
    C[0] = 6;
    cout << 2 << endl << 3 << endl;
    bool pos = true;
    for (int i = 3; i <= N; ++i) {
        cout << C[!pos] + 1 << endl;
        C[pos] = C[!pos] * (C[!pos] + 1);
        pos = !pos;
    }
    
    return 0;
}
