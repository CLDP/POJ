#include <iostream>
#include <cstdio>
#include <complex>
#include <algorithm>
using namespace std;

const long double EPS = 1e-16;
const int MAXN = 210;
const long double PI = acos(-1.0);
const long double INF = 1e6;
typedef complex<long double> point;

inline int dbcmp(long double d) { return d < -EPS ? -1 : (d > EPS);}
long double operator ^ (point a, point b) { return imag(conj(a) * b);}

struct line {
    point a, b;
    long double angle;
    line() {}
    line(point _a, point _b) :a(_a), b(_b) {angle = arg(_b - _a);}
    bool operator < (line const &l) const {
        return dbcmp(angle - l.angle) < 0 ||
               dbcmp(angle - l.angle) == 0 && dbcmp(b - a ^ l.b - a) < 0;
    }
};

point operator * (const line &u, const line &v) {
    point ret = u.a;
    long double t = u.a - v.a ^ v.b - v.a;
    long double s = u.a - u.b ^ v.b - v.a;
    return ret + (u.b - u.a) * t / s;
}

point p[MAXN], p2[MAXN];
line l[MAXN];
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

long double area(point *p, int n) {
    p[n] = p[0];
    long double sum = 0;
    for (int i = 0; i < n; ++i) sum += p[i] ^ p[i + 1];
    return fabs(sum) / 2;
}


line equation_to_line(long double A, long double B, long double C) {
    // change Ax + by + C < 0 to line, at most one of ABC could be zero
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
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> A[i] >> B[i] >> C[i];
    
    for (int i = 0; i < n; ++i) {
        int lsz = 0;
        bool flag = true;
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            if ((A[i] == A[j]) + (B[i] == B[j]) + (C[i] == C[j]) >= 2) {
                if (A[i] > A[j] || B[i] > B[j] || C[i] > C[j]) continue;
                flag = false;
                break;
            }
            long double diffA = 1.0 * (A[j] - A[i]) / (A[j] * A[i]);
            long double diffB = 1.0 * (B[j] - B[i]) / (B[j] * B[i]);
            long double diffC = 1.0 * (C[j] - C[i]) / (C[j] * C[i]);
            l[lsz++] = equation_to_line(diffA, diffB, diffC);
        }
        if (!flag) {
            cout << "No" << endl;
            continue;
        }
        
        l[lsz++] = line(point(0, 0), point(INF, 0));
        l[lsz++] = line(point(INF, 0), point(INF, INF));
        l[lsz++] = line(point(INF, INF), point(0, INF));
        l[lsz++] = line(point(0, INF), point(0, 0));
        int psz = gethe(l, lsz, p);
        if (area(p, psz) > EPS) cout << "Yes" << endl; else cout << "No" << endl;
    }
    
    return 0;
}
