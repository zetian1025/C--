#include "Model.h"
using namespace std;

class Solution {
public:
    const int Mod = 1e9+7;
    int findPaths(int m, int n, int N, int i, int j) {
        queue<pair<int, int>> q;
        q.push({i, j});
        vector<pair<int, int>> dir = {{1,0}, {-1,0}, {0,1}, {0,-1}};
        
        int time[m][n];
        int tempTime[m][n];
        memset(time, 0, sizeof(time));
        time[i][j] = 1;

        long long cnt = 0;
        while (N-- > 0) {
            int k = q.size();
            memset(tempTime, 0, sizeof(tempTime));
            while (k-- > 0) {
                pair<int, int> p = q.front();
                q.pop();
                
                int x = p.first;
                int y = p.second;
                for (auto& d : dir) {
                    int tx = x + d.first;
                    int ty = y + d.second;
                    if (tx>=0 && ty>=0 && tx<m && ty<n) {
                        if (tempTime[tx][ty] == 0) {
                            q.push({tx, ty});
                        }
                        tempTime[tx][ty]++;
                    }
                    else cnt+=time[x][y];
                }
            }

            for (int i=0; i<m; i++) {
                for (int j=0; j<n; j++) {
                    time[i][j] = tempTime[i][j];
                }
            }
        }
        return cnt%Mod;
    }
};;

int main(){
    Solution solution;
    int ans = solution.findPaths(2,3,8,1,0);
    cout << ans << endl;
    return 0;
}