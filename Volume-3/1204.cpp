#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int MAXN = 1005;
const int MAXM = 100005;
const int MX[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int MY[8] = {0, 1, 1, 1, 0, -1, -1, -1};

struct Node {
    int id;
    Node *nxt[26], *fail;
} *root, MEMORY[MAXM], *que[MAXM];


int n, row, col;
char msg[MAXN][MAXN];
int k = 0, len[MAXN];
int ans[MAXN][3];


void insert(int id, char str[]) {
    Node *p = root;
    for(int i = 0; str[i]; ++i) {
        int idx = str[i] - 'A';
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
        for (int i = 0; i < 26; ++i) {
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

void query(int fr, int fc, int dir) {
    int r = fr, c = fc;
    Node *p = root;
    int times = 0;
    while (r >= 0 && r < row && c >= 0 && c < col) {
        int idx = msg[r][c] - 'A';
        while (p->nxt[idx] == 0 && p != root) p = p->fail;
        p = p->nxt[idx];
        if (p == 0) p = root;
        // Use tmp to traverse all solutions
        for (Node *tmp = p; tmp != 0 && tmp->id != -1; tmp = tmp->fail) {
            int id = tmp->id;
            ans[id][0] = r - (len[id] - 1) * MX[dir];
            ans[id][1] = c - (len[id] - 1) * MY[dir];
            ans[id][2] = dir;
            tmp->id = -1;
        }
        r += MX[dir];
        c += MY[dir];
    }
}


int main() {
    scanf("%d%d%d", &row, &col, &n);
    root = &MEMORY[k++];
    for (int i = 0; i < row; ++i) scanf("%s", msg[i]);
    for (int i = 0; i < n; ++i) {
        char str[MAXN];
        scanf("%s", str);
        len[i] = strlen(str);
        insert(i, str);
    }
    AC();
    for (int i = 0; i < row; ++i) {
        query(i, 0, 1);
        query(i, 0, 2);
        query(i, 0, 3);
        query(i, col - 1, 5);
        query(i, col - 1, 6);
        query(i, col - 1, 7);
    }
    
    for (int i = 0; i < col; ++i) {
        query(0, i, 3);
        query(0, i, 4);
        query(0, i, 5);
        query(row - 1, i, 7);
        query(row - 1, i, 0);
        query(row - 1, i, 1);
    }
    
    for (int i = 0; i < n; i ++) {
        printf("%d %d %c\n", ans[i][0], ans[i][1], ans[i][2] + 'A');
    }
    
    return 0;
}
