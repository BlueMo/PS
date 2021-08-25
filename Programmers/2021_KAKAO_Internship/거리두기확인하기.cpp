#include <string>
#include <vector>
#include <algorithm>
#include <tuple>
#include <queue>
using namespace std;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;

vector<int> solution(vector<vector<string>> places) {
    const int n = 5;
    const int dx[4] = {1, -1, 0, 0}, dy[4] = {0, 0, -1, 1};
    vector<int> answer;
    
    for (auto p : places){
        vector<vector<int>> place_map(n, vector<int>(n, 0));
        vector<pii> candidate_pos;
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                if (p[i][j] == 'P'){
                    candidate_pos.push_back({i, j});
                    place_map[i][j] = 2;
                }
                else if (p[i][j] == 'O') place_map[i][j] = 1;
            }
        }
        bool end_flag = 0;
        for (auto [pos_y, pos_x] : candidate_pos){
            queue<tiii> q;
            vector<vector<bool>> chk(n, vector<bool>(n, 0));
            q.push({pos_y, pos_x, 0});
            chk[pos_y][pos_x] = 1;
            while (!q.empty()){
                auto [y, x, d] = q.front(); q.pop();
                
                for (int i = 0; i < 4; i++){
                    int ny = y + dy[i];
                    int nx = x + dx[i];
                    if (ny < 0 || nx < 0 || ny == n || nx == n) continue;
                    if (chk[ny][nx] || !place_map[ny][nx]) continue;
                    if (place_map[ny][nx] == 2 && d <= 1){
                        answer.push_back(0);
                        end_flag = 1;
                        break;
                    }
                    chk[ny][nx] = 1;
                    q.push({ny, nx, d+1});
                }
                if (end_flag) break;
            }
            if (end_flag) break;
        }
        if (!end_flag) answer.push_back(1);
    }    
    
    return answer;
}
int main(){
    return 0;
}