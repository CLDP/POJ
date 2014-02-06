#include <iostream>
#include <cstdio>
#include <complex>
#include <algorithm>
using namespace std;

const double EPS = 1e-8;
const int MAXN = 20010;
const double PI = acos(-1.0);
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

point p[MAXN];
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

double area(point *p, int n) {
    p[n] = p[0];
    double sum = 0;
    for (int i = 0; i < n; ++i) sum += p[i] ^ p[i + 1];
    return fabs(sum) / 2;
}

int main() {
    int n, lsz = 0, psz;
    cin >> n;
    double x1, y1, x2, y2;
    for (int i = 0; i < n; ++i) {
        cin >> x1 >> y1 >> x2 >> y2;
        l[lsz++] = line(point(x1, y1), point(x2,y2));
    }
    
    l[lsz++] = line(point(0, 0), point(10000, 0));
    l[lsz++] = line(point(10000, 0), point(10000, 10000));
    l[lsz++] = line(point(10000, 10000), point(0, 10000));
    l[lsz++] = line(point(0, 10000), point(0,0));
    psz = gethe(l, lsz, p);
    printf("%.1lf\n", area(p, psz));
    return 0;
}
