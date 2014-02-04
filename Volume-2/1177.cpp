#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <string>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;

const int MAXK = 10010;


struct seg {
    int a, b, c, d;
};


int n;
vector<seg> x, y;
int f[MAXK * 2];


bool compare(const seg &a, const seg &b) {
    if (a.c < b.c) return true;
    if (a.c > b.c) return false;
    if (a.d == b.d) return false;
    if (a.d == 1) return true;
    return false;
}


int main() {
    cin >> n;
    int a, b, c, d;
    seg newnode;
    for (int i = 0; i < n; ++i) {
        cin >> a >> b >> c >> d;
        newnode.a = min(a, c);
        newnode.b = max(a, c);
        newnode.c = min(b, d);
        newnode.d = 1;
        x.push_back(newnode);
        
        newnode.c = max(b, d);
        newnode.d = 2;
        x.push_back(newnode);
        
        newnode.a = min(b, d);
        newnode.b = max(b, d);
        newnode.c = min(a, c);
        newnode.d = 1;
        y.push_back(newnode);
        
        newnode.c = max(a, c);
        newnode.d = 2;
        y.push_back(newnode);
    }
    
    sort(x.begin(), x.end(), compare);
    sort(y.begin(), y.end(), compare);
    
    int ans = 0;
    
    for (int i = 0; i < x.size(); ++i) {
        if (x[i].d == 1) {
            for (int j = x[i].a; j < x[i].b; ++j) {
                ++f[j + MAXK];
                if (f[j + MAXK] == 1) ++ans;
            }
        } else {
            for (int j = x[i].a; j < x[i].b; ++j) {
                --f[j + MAXK];
                if (f[j + MAXK] == 0) ++ans;
            }
        }
    }
    
    for (int i = 0; i < y.size(); ++i) {
        if (y[i].d == 1) {
            for (int j = y[i].a; j < y[i].b; ++j) {
                ++f[j + MAXK];
                if (f[j + MAXK] == 1) ++ans;
            }
        } else {
            for (int j = y[i].a; j < y[i].b; ++j) {
                --f[j + MAXK];
                if (f[j + MAXK] == 0) ++ans;
            }
        }
    }
    
    cout << ans << endl;
    
    return 0;
}
