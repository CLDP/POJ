#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

vector<pair<int, int> > x[25];
int need[24], num[24];

bool check(int NUM) {
    for (int i = 0; i < 25; ++i) x[i].clear();
    x[0].push_back(make_pair(24, NUM));
    for (int i = 0; i < 24; ++i) {
        if (i <= 7) 
            x[i + 17].push_back(make_pair(i + 1, need[i] - NUM));
        else
            x[i - 7].push_back(make_pair(i + 1, need[i]));
        x[i].push_back(make_pair(i + 1, 0));
        x[i + 1].push_back(make_pair(i, -num[i]));
    }
    vector<int> d(25, 0);
    vector<bool> z(25, false);
    for (int k = 0; k < 24; ++k) {
        bool flag = true;
        for (int i = 0; i < 25; ++i)
         for (int j = 0; j < x[i].size(); ++j)
          if (d[i] + x[i][j].second > d[x[i][j].first]) {
              d[x[i][j].first] = d[i] + x[i][j].second;
              flag = false;
          }
        if (flag) break;
    }
    
    for (int i = 1; i < 25; ++i)
     if (d[i] - d[i-1] > num[i - 1]) return false;
    for (int i = 0; i < 25; ++i)
     for (int j = 0; j < x[i].size(); ++j)
      if (d[i] + x[i][j].second > d[x[i][j].first]) return false;
    
    return d[24] == NUM;
}


int main() {
    int times;
    cin >> times;
    while (times--) {
        for (int i = 0; i < 24; ++i) {
            cin >> need[i];
            num[i] = 0;
        }
        int M, a;
        cin >> M;
        for (int i = 0; i < M; ++i) {
            cin >> a;
            ++num[a];
        }
        int ans = -1;
        for (int i = 0; i <= M; ++i) {
            if (check(i)) {
                ans = i;
                break;
            }
        }
        if (ans > 0) cout << ans << endl; else cout << "No Solution" << endl;
    }
    return 0;
}
