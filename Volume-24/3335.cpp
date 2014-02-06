#include <iostream>
#include <cstdio>
#include <complex>
#include <algorithm>
using namespace std;

const double EPS = 1e-8;
const int MAXN = 210;
const double PI = acos(-1.0);
const double INF = 1e10;
typedef complex<double> point;

inline int dbcmp(double d) { return d < -EPS ? -1 : (d > EPS);}
double operator ^ (point a, point b) { return imag(conj(a) * b);}

struct line {
    point a, b;
    double angle;
    line() {}
    line(point _a, point _b) :a(_a), b(_b) {angle = arg(_b - _a);}
    bool operator < (line const &l) const {
        return dbcmp(angle - l.angle) < 0 ||
               dbcmp(angle - l.angle) == 0 && dbcmp(b - a ^ l.b - a) < 0;
    }
};

point operator * (const line &u, const line &v) {
    point ret = u.a;
    double t = u.a - v.a ^ v.b - v.a;
    double s = u.a - u.b ^ v.b - v.a;
    return ret + (u.b - u.a) * t / s;
}

point p[MAXN], p2[MAXN];
line l[MAXN];
int e[MAXN];

bool onLeft(point p1, line u){
    return dbcmp(p1 - u.a ^ u.b - u.a) <= 0;
}

bool uniquecmp(line u, line v){
    return dbcmp(u.angle - v.angle) == 0;
}

// Get the core of half plane and save in l
int gethe(line *l, int lsz, point *p) {
    int eb = 0, ee = 2, pb = 0, pe = 1, psz = 1;
    sort(l, l + lsz);
    p[lsz] = p[0];
    // left only one for each slope
    lsz = distance(l, unique(l, l + lsz, uniquecmp));
    e[0] = 0;
    e[1] = 1;
    p[0] = l[0] * l[1];
    for (int i = 2; i < lsz; ++i) {
        while (pb != pe && !onLeft(p[pe - 1], l[i])) --pe, --ee;
        while (pb != pe && !onLeft(p[pb], l[i])) ++pb, ++eb;
        p[pe++] = l[i] * l[e[ee - 1]];
        e[ee++] = i;
    }
    while (pb != pe && !onLeft(p[pe - 1], l[e[eb]])) --pe, --ee;
    while (pb != pe && !onLeft(p[pb], l[e[ee - 1]])) ++pb, ++eb;
    p[pe++] = l[e[pb]] * l[e[ee - 1]];
    psz = pe - pb;
    for (int i = 0; pb != pe; ++i) p[i] = p[pb++];
    return psz;
}


int main() {
    int n, times;
    cin >> times;
    while (times--) {
        cin >> n;
        int lsz = 0, psz = 0;
        double x1, y1;
        for (int i = 0; i < n; ++i) {
            cin >> x1 >> y1;
            p2[i] = point(x1, y1);
        }
        for (int i = 1; i < n; ++i) {
            l[lsz++] = line(p2[i], p2[i - 1]);
        }
        l[lsz++] = line(p2[0], p2[n - 1]);
        psz += gethe(l, lsz, p);
        // Special judge for no solution
        if (psz < 3) cout << "NO" << endl; else cout << "YES" << endl;
    }
    return 0;
}
