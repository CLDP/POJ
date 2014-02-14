#include <cstdio>
#include <string>
#include <set>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 10000;
const int MAXM = 5000000;

struct Node {
    int id;
    Node *nxt[2], *fail;
} *root, MEMORY[MAXN], *que[MAXN];


int n, row, col;
int k = 0;
char msg[MAXM];
vector<string> ANS;
vector<int> NUM;


void insert(int id, string str) {
    Node *p = root;
    for(int i = 0; i < str.size(); ++i) {
        int idx = str[i] - '0';
        if (p->nxt[idx] == 0) {
            MEMORY[k].id = -1;
            MEMORY[k].fail = 0;
            memset(MEMORY[k].nxt, 0, sizeof(MEMORY[k].nxt));
            p->nxt[idx] = &MEMORY[k++];
        }
        p = p->nxt[idx];
    }
    p->id = id;
}

void AC() {
    int head = 0, tail = 0;
    root->fail = 0;
    que[tail++] = root;
    while (head < tail) {
        Node *tmp = que[head++];
        for (int i = 0; i < 2; ++i) {
            if (tmp->nxt[i] == 0) continue;
            if (tmp == root) {
                tmp->nxt[i]->fail = root;
            } else {
                Node *p;
                for (p = tmp->fail; p != 0; p = p->fail) {
                    if (p->nxt[i] != 0) {
                        tmp->nxt[i]->fail = p->nxt[i];
                        break;
                    }
                }
                if (p == 0) tmp->nxt[i]->fail = root;
            }
            que[tail++] = tmp->nxt[i];
        }
    }
}

void query() {
    int pos = 0, len = strlen(msg);
    Node *p = root;
    while (pos < len - 1) {
        int idx = msg[pos] - '0';
        while (p->nxt[idx] == 0 && p != root) p = p->fail;
        p = p->nxt[idx];
        if (p == 0) p = root;
        // Use tmp to traverse all solutions
        for (Node *tmp = p; tmp != 0 && tmp->id != -1; tmp = tmp->fail) {
            ++NUM[tmp->id];
        }
        ++pos;
    }
}

int dfs(int a, string p) {
    if (a == 0) {
        ANS.push_back(p);
        NUM.push_back(0);
        insert(ANS.size() - 1, p);
    } else {
        dfs(a - 1, p + '0');
        dfs(a - 1, p + '1');
    }
    return 0;
}

bool compare(const string &A, const string &B) {
    if (A.size() != B.size()) return A.size() > B.size();
    return A > B;
}

int main() {
    int minX, maxX, N;
    scanf("%d%d%d", &minX, &maxX, &N);
    scanf("%s", msg);
    root = &MEMORY[k++];
    root->id = -1;
    
    for (int i = minX; i <= maxX; ++i) dfs(i, "");
    AC();
    query();
    set<pair<int, string> > C;
    
    for (int i = 0; i < ANS.size(); ++i) C.insert(make_pair(NUM[i], ANS[i]));
    
    set<pair<int, string> >::reverse_iterator iter = C.rbegin();
    while (iter != C.rend()) {
        int temp = iter->first;
        if (temp == 0) break;
        vector<string> ans;
        while (iter->first == temp) {
            ans.push_back(iter->second);
            ++iter;
            if (iter == C.rend()) break;
        }
        sort(ans.begin(), ans.end(), compare);
        cout << temp;
        for (int i = 0; i < ans.size(); ++i) cout << " " << ans[i];
        cout << endl;
        --N;
        if (N == 0) break;
    }
    
    return 0;
}
