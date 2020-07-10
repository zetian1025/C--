#include <iostream>
#include <queue>
using namespace std;
int JosephusRing(int m,int n);
int main(){
    int m,n;
    cin>>m>>n;
    int Survive = JosephusRing(m,n);
    cout<<"Person #"<<Survive<<" survived.\n"<<endl;
    return 0;
}

int JosephusRing(int m,int n){
    queue<int> Q;
    for (int i=1;i<=m;i++){
        Q.push(i);
    }
    while(Q.size() != 1){
        for (int i=0;i<n;i++){
            int temp = Q.front();
            Q.pop();
            Q.push(temp);
        }
        int DeadPerson = Q.front();
        Q.pop();
        cout<<"Person #"<<DeadPerson<<" died."<<endl;
    }
    int LivePerson = Q.front();
    return LivePerson;
}