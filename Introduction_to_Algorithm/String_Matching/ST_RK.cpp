#include <iostream>
#include <cmath>
#include <cstring>
#define d 10
using namespace std;

int main(){
    string T, P;
    cin >> T >> P;

    int q;
    cin >> q;
    
    int n = T.size();
    int m = P.size();
    int h = (int)pow(d, m-1) % q;
    int p = 0;
    int t = 0;
    for (int i=0; i<m; i++) {
        t = (d*t + (T[i] - '0')) % q;
        p = (d*p + (P[i] - '0')) % q;
    }

    for (int i=0; i<=n-m; i++) {
        if (t == p) {
            int k = 0;
            for (; k<m; k++) {
                if (P[k] == T[k+i]) continue;
                else break;
            }
            if (k == m) {
                cout << "Pattern found at index " << i << endl;
            }
        }
        if (i < n-m) {
            t = (d*(t - (T[i]-'0')*h)) + (T[i+m] - '0') % q;
            while (t < 0) t+=q;
        }
    }
    return 0;
}