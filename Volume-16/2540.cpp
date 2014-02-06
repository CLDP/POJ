#include <iostream>
#include <cstdio>
#include <complex>
#include <algorithm>
using namespace std;

const double EPS = 1e-8;
const int MAXN = 210;
const double PI = acos(-1.0);
const double INF = 10;
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
line l[MAXN], l2[MAXN];
int e[MAXN], A[MAXN], B[MAXN], C[MAXN];

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

line equation_to_line(double  A, double  B, double  C) {
    // change Ax + by + C < 0 to line, at most one of ABC could be zero
    // if A == 0 and B == 0, then C == 0
    if (C == 0) {
        return line(point(0, 0), point(-B, A));
    }
    if (A == 0) {
        return line(point(0, -C / B), point(-B, -C / B));
    }
    if (B == 0) {
        return line(point(-C / A, 0), point(-C / A, A));
    }
    if (A * B * C > 0) {
        return line(point(0, -C / B), point(-C / A , 0));
    } else 
    if (A * B * C < 0) {
        return line(point(-C / A , 0), point(0, -C / B));
    }
}

int main() {
    int lsz = 0;
    string P;
    double x1, y1, x2, y2;
    x1 = y1 = 0;
    l2[lsz++] = line(point(0, 0), point(INF, 0));
    l2[lsz++] = line(point(INF, 0), point(INF, INF));
    l2[lsz++] = line(point(INF, INF), point(0, INF));
    l2[lsz++] = line(point(0, INF), point(0, 0));
    bool flag = false;
    while (cin >> x2 >> y2 >> P) {
        if (x2 == x1 && y2 == y1) continue;
        if (P == "Same") flag = true;
        if (flag) {
            cout << "0.00" << endl;
            continue;
        }
        if (x1 == x2) {
            if ((P == "Hotter") == (y2 > y1))
                l2[lsz++] = line(point(x1, (y1 + y2) / 2), point(x1 + 1, (y1 + y2) / 2));
            else 
                l2[lsz++] = line(point(x1, (y1 + y2) / 2), point(x1 - 1, (y1 + y2) / 2));
        } else
        if (y1 == y2) {
            if ((P == "Hotter") == (x1 < x2)) 
                l2[lsz++] = line(point((x1 + x2) / 2, y1), point((x1 + x2) / 2, y1 - 1));
            else
                l2[lsz++] = line(point((x1 + x2) / 2, y1), point((x1 + x2) / 2, y1 + 1));
        } else
        if (x1 * x1 + y1 * y1 == x2 * x2 + y2 * y2) {
            point A = point(0, 0), B = point(y2 - y1, x1 - x2);
            if ((P == "Hotter") == (onLeft(point(x2, y2), line(A, B))))
                l2[lsz++] = line(A, B); 
            else 
                l2[lsz++] = line(B, A);
        } else {
            double sqrtD = ((x2 * x2 + y2 * y2) - (x1 * x1 + y1 * y1)) / 2;
            point A = point(0, sqrtD / (y2 - y1)), B = point(sqrtD / (x2 - x1), 0);
            if ((P == "Hotter") == (onLeft(point(x2, y2), line(A, B))))
                l2[lsz++] = line(A, B); 
            else 
                l2[lsz++] = line(B, A);
        }
        for (int i = 0; i < lsz; ++i) l[i] = l2[i];
        int psz = gethe(l, lsz, p);
        printf("%.2lf\n", area(p, psz));
        x1 = x2, y1 = y2;
    }
    
    return 0;
}
