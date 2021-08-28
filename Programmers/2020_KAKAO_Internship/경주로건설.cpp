#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <tuple>
using namespace std;
typedef tuple<int, int, int, int> queue_value;
int solution(vector<vector<int>> board) {
    int answer = 0, n = board.size();
    const int INF = 0x7fffffff;
    const int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
    vector<vector<vector<int>>> min_cost(n, vector<vector<int>>(n, vector<int>(2, INF)));
    queue<queue_value> q;
    
    q.push({0, 0, 0, 0});  // 0: row
    q.push({0, 0, 1, 0});  // 1: col
    min_cost[0][0][0] = min_cost[0][0][1] = 0;
    
    while (!q.empty()){
        auto [y, x, dir, cost] = q.front(); q.pop();
        if (cost > min_cost[y][x][dir]) continue;
        
        for (int i = 0; i < 4; i++){
            int nx = x + dx[i], ny = y + dy[i], ndir = i/2;
            if (nx < 0 || ny < 0 || nx == n || ny == n) continue;
            if (board[ny][nx]) continue;
            if (dir == ndir && cost + 100 < min_cost[ny][nx][ndir]){
                min_cost[ny][nx][ndir] = cost + 100;
                q.push({ny, nx, ndir, min_cost[ny][nx][ndir]});
            }
            else if (dir != ndir && cost + 600 < min_cost[ny][nx][ndir]){
                min_cost[ny][nx][ndir] = cost + 600;
                q.push({ny, nx, ndir, min_cost[ny][nx][ndir]});
            }
        }
    }
    answer = min(min_cost[n-1][n-1][0], min_cost[n-1][n-1][1]);
    return answer;
}
int main(){
    return 0;
}