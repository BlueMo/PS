#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

struct P{
    int y, x, dist;
    bool is_pass;
};

char t;
int N, M;
bool MAP[1001][1001], chk[1001][1001][2];
queue<P> q;
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> N >> M;
    for (int i = 1; i <= N; ++i){
        for (int j = 1; j <= M; ++j){
            cin >> t;
            MAP[i][j] = t - '0';
        }
    }
    q.push({1, 1, 1, 0});
    while (!q.empty()){
        P h = q.front();
        q.pop();
        
        if (h.y == N && h.x == M){
            cout << h.dist;
            return 0;
        }

        for (int i = 0; i < 4; ++i){
            int x = h.x + "1102"[i] - '1';
            int y = h.y + "0211"[i] - '1';

            if (x == 0 || y == 0 || x > M || y > N) continue;
            if (!MAP[y][x] && !chk[y][x][h.is_pass]){
                chk[y][x][h.is_pass] = 1;
                q.push({y, x, h.dist + 1, h.is_pass});
            }
            else if (MAP[y][x] && !h.is_pass){
                chk[y][x][1] = 1;
                q.push({y, x, h.dist + 1, 1});
            }
        }
    }
    cout << -1;
    return 0;
}