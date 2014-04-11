#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 10010;
const double EPS = 1e-8;
const double PI = acos(-1.0);

struct CPoint { double x, y; };

double sqr(double x) { return x * x; }

int dcmp(double x) {
    if (x < -EPS) return -1; else return (x > EPS);
}

double cross(CPoint p0, CPoint p1, CPoint p2) {
    return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
}

double dot(CPoint p0, CPoint p1, CPoint p2) {
    return (p1.x - p0.x) * (p2.x - p0.x) + (p1.y - p0.y) * (p2.y - p0.y);
}

double dissqr(CPoint p1, CPoint p2) {
    return sqr(p1.x - p2.x) + sqr(p1.y - p2.y);
}

double dis(CPoint p1, CPoint p2) {
    return sqrt(dissqr(p1, p2));
}

int PointEqual(const CPoint &p1, const CPoint &p2) {
    return dcmp(p1.x - p2.x) == 0 && dcmp(p1.y - p2.y) == 0;
}


CPoint bp;  // Used for GrahamScan, lowest point

bool PolarCmp(const CPoint &p1, const CPoint &p2) {
    int u = dcmp(cross(bp, p1, p2));
    return u > 0 || (u == 0 && dcmp(dissqr(bp, p1) - dissqr(bp, p2)) < 0);
}


int GrahamScan(CPoint ch[], int n, int &m) {
    int k = 0;
    for (int i = 0; i < n; ++i) {
        int u = dcmp(ch[i].x - ch[k].x);
        int v = dcmp(ch[i].y - ch[k].y);
        if (v < 0 || (v == 0 && u < 0)) k = i;
    }
    bp = ch[k];
    sort(ch, ch + n, PolarCmp);
    n = unique(ch, ch + n, PointEqual) - ch;
    if (n <= 1) {
        m = n;
        return 0;
    }
    if (dcmp(cross(ch[0], ch[1], ch[n - 1])) == 0) {
        m = 2;
        ch[1] = ch[n - 1];
        return 0;
    }
    ch[n++] = ch[0];
    int i = 1;
    for (int j = 2; j < n; ++j) {
        while (i > 0 && dcmp(cross(ch[i - 1], ch[i], ch[j])) < 0) --i;
        ch[++i] = ch[j];
    }
    m = i;
    return 0; 
}

CPoint ch[MAXN];

int main() {
    int N;
    double DD;
    cin >> N >> DD;
    for (int i = 0; i < N; ++i) cin >> ch[i].x >> ch[i].y;
    int M;
    GrahamScan(ch, N, M);
    double ans = 0;
    for (int i = 0; i < M; ++i) ans += dis(ch[i], ch[(i + 1) % M]);
    ans += PI * DD * 2;
    cout << (int)(ans + 0.5) << endl;
    return 0;
}
