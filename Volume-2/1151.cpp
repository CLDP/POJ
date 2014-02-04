#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <cstdio>
#include <algorithm>
using namespace std;


struct rect {
    double x1, y1, x2, y2;
};


vector<rect> x;




bool get_boundary(double x1, double x2, double x3, double x4, double &k1, double &k2) {
    k1 = max(x1, x3);
    k2 = min(x2, x4);
    if (k1 >= k2) return false;
    return true;
}

int add_one(double x1, double y1, double x2, double y2) {
    rect p;
    p.x1 = x1;
    p.y1 = y1;
    p.x2 = x2;
    p.y2 = y2;
    x.push_back(p);
    return 0;
}

int add(double a, double b, double c, double d) {
    int j = 0, len = x.size();
    
    while (j < len) {
        double k1, k2, k3, k4;
        if (!get_boundary(x[j].x1, x[j].x2, a, c, k1, k2)) {
            ++j;
            continue;
        }
        
        if (!get_boundary(x[j].y1, x[j].y2, b, d, k3, k4)) {
            ++j;
            continue;
        }
        
        if (x[j].x1 < k1) add_one(x[j].x1, x[j].y1, k1, x[j].y2);
        if (k2 < x[j].x2) add_one(k2, x[j].y1, x[j].x2, x[j].y2);
        if (x[j].y1 < k3) add_one(k1, x[j].y1, k2, k3);
        if (k4 < x[j].y2) add_one(k1, k4, k2, x[j].y2);
        x.erase(x.begin() + j);
        --len;
    }
    
    add_one(a, b, c, d);
    return 0;
}



int main() {
    int N, times = 0;
    while (cin >> N) {
        if (N == 0) break;
        ++times;
        x.clear();
        for (int i = 0; i < N; ++i) {
            double a, b, c, d;
            cin >> a >> b >> c >> d;
            add(a, b, c, d);
        }
        
        double ans = 0;
        for (int i = 0; i < x.size(); ++i) ans += (x[i].x2 - x[i].x1) * (x[i].y2 - x[i].y1);
        
        cout << "Test case #" << times << endl;
        cout << "Total explored area: ";
        printf("%.2lf\n\n", ans);
    }
    return 0;
}
