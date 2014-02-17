#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

int main() {
    int times, N;
    cin >> times;
    while (times--) {
        cin >> N;
        long double P = 1;
        int ans = 1;
        for (int i = 2; i <= N; ++i) {
            P = P * i;
            
            if (P > 1e200) {
                int temp = log10(P);
                ans += temp;
                P /= pow(10.0, temp);
            }
        }
        ans += (int)log10(P);
        cout << ans << endl;
    }
    
    return 0;
}
