#include <cstdio>
#include <string>
#include <map>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1000;
const int km = 10000;


class HP {
    public:
        int len, s[100];
        HP() {(*this) = 0;};                  
        HP(int inte) {(*this) = inte;};   
        friend ostream &operator << (ostream &cout, const HP &x);
        HP operator = (int inte);
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

int HP::Compare(const HP &y) {
    if (len > y.len) return 1;
    if (len < y.len) return -1;
    int i = len;
    while ((i > 1) && (s[i] == y.s[i])) --i;
    return s[i] - y.s[i];
}

struct Node {
    int id, pos;
    Node *nxt[100], *fail;
} *root, MEMORY[MAXN], *que[MAXN];


int n;
int k = 0;
HP f[2][MAXN];
map<char, int> C;

void insert(int id, char str[]) {
    Node *p = root;
    for(int i = 0; i < strlen(str); ++i) {
        int idx = C[str[i]];
        if (p->nxt[idx] == 0) {
            MEMORY[k].id = -1;
            MEMORY[k].fail = 0;
            MEMORY[k].pos = k;
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
        for (int i = 0; i < 100; ++i) {
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

char alpha[MAXN];


int main() {
    int N, M, P;
    cin >> N >> M >> P;
    gets(alpha);
    gets(alpha);
    for (int i = 0; i < N; ++i) C[alpha[i]] = i;
    
    root = &MEMORY[k++];
    root->id = -1;
    root->pos = 0;
    for (int i = 0; i < P; ++i) {
        char Q[MAXN];
        gets(Q);
        insert(1, Q);
    }
    AC();
    
    f[0][0] = 1;
    for (int j = 1; j < k; ++j) f[0][j] = 0;
    bool todo = true;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < k; ++j) f[todo][j] = 0;
        for (int j = 0; j < k; ++j) {
            if (f[!todo][j].Compare(0) > 0) {
                for (int l = 0; l < N; ++l) {
                    Node *curr = &MEMORY[j];
                    int idx = C[alpha[l]];
                    bool flag = false;
                    while (curr->nxt[idx] == 0 && curr != root) {
                        curr = curr->fail;
                        flag |= curr->id == 1;
                    }
                    curr = curr->nxt[idx];
                    if (curr == 0) curr = root;
                    flag |= curr->id == 1;
                    for (Node *tmp = curr; tmp != 0; tmp = tmp->fail) flag |= tmp->id == 1;
                    
                    if (!flag) f[todo][curr->pos] = f[todo][curr->pos] + f[!todo][j];
                }
            }
        }
        todo = !todo;
    }
    
    HP ans = 0;
    for (int i = 0; i < k; ++i) ans = ans + f[!todo][i];
    cout << ans << endl;
    
    return 0;
}
