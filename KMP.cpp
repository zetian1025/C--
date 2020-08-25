#include <iostream>
#include <vector>
using namespace std;

void func(string p);

int main(){
    string p;
    cin >> p;
    func(p);
    return 0;
}

//eg:   P = "ababac"
//then pai=[0,0,0,1,2,3]

void func(string P){
    int m = P.length();
    vector<int> pai(m, 0);
    int k = 0;
    for (int i=2; i<m; i++) {
        while (k>0 && P[k] != P[i-1]) k = pai[k];
        if (P[k] == P[i-1]) k++;
        pai[i] = k;
    }
    for (int i : pai) cout << i << endl;
}