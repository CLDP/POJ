#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <cstdio>
#include <algorithm>
using namespace std;

const string P[9] = {"ABDE", "ABC", "BCEF", "ADG", "BDEFH", "CFI", "DEGH", "GHI", "EFHI"};

int x[9];
int z[9];

bool dfs(int a, int b) {
    if (b == 9) return false;
    if (a == 0) {
        bool flag = true;
        for (int i = 0; i < 9; ++i) flag &= x[i] == 0;
        if (flag) {
            vector<int> ans;
            for (int i = 0; i < 9; ++i) {
                while (z[i]-- > 0) ans.push_back(i + 1);
            }
            for (int i = 0; i < ans.size() - 1; ++i) cout << ans[i] << " "; 
            cout << ans[ans.size() - 1] << endl;
        }
        return flag;
    }
    if (z[b] == 3) return dfs(a, b + 1);
    ++z[b];
    for (int i = 0; i < P[b].size(); ++i) {
        x[P[b][i] - 'A'] = (x[P[b][i] - 'A'] + 1) % 4;
    }
    if (dfs(a - 1, b)) return true;
    for (int i = 0; i < P[b].size(); ++i) {
        x[P[b][i] - 'A'] = (x[P[b][i] - 'A'] + 3) % 4;
    }
    --z[b];
    return dfs(a, b + 1);
}


int main() {
    for (int i = 0; i < 9; ++i) cin >> x[i];
    for (int i = 0; i <= 27; ++i) 
     if (dfs(i, 0)) break;
    
    return 0;
}
