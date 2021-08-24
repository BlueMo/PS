#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;
typedef pair<int, int> pii;

bool is_same_shape(vector<pii> board, vector<pii> block){
    if (board.size() != block.size()) return false;
    
    for (int i = 0; i < board.size(); i++){
        if (board[i].first != block[i].first || board[i].second != block[i].second) return false;
    }
    return true;
}

void rotate_block(vector<pii> &block){
    pii minValue = {100, 100};
    for (auto &b : block){
        int t = b.first;
        b.first = -b.second;
        b.second = t;
        
        if (minValue.first > b.first) minValue = b;
        else if (minValue.first == b.first && minValue.second > b.second) minValue = b;
    }
    for (auto &b : block){
        b.first -= minValue.first;
        b.second -= minValue.second;
    }
    sort(block.begin(), block.end());
}

int solution(vector<vector<int>> game_board, vector<vector<int>> table) {
    int answer = 0, N = game_board.size(), M = game_board[0].size(), cnt = 0;
    int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
    vector<vector<bool>> chk(N, vector<bool>(M, false));
    vector<vector<pii>> blank;

    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            if (game_board[i][j] || chk[i][j]) continue;
            vector<pii> vec_pii;
            queue<pii> q;
            blank.push_back(vec_pii);
            blank[cnt].push_back({0, 0});
            q.push({i, j});
            chk[i][j] = 1;
            while (!q.empty()){
                pii h = q.front(); q.pop();
                for (int k = 0; k < 4; k++){
                    int y = h.first + dy[k];
                    int x = h.second + dx[k];
                    if (x < 0 || y < 0 || x == M || y == N) continue;
                    if (game_board[y][x] || chk[y][x]) continue;
                    chk[y][x] = 1;
                    blank[cnt].push_back({y - i, x - j});
                    q.push({y, x});
                }
            }
            sort(blank[cnt].begin(), blank[cnt].end());
            cnt++;
        }
    }
    
    fill(chk.begin(), chk.end(), vector<bool>(M, false));
    vector<bool> is_filled(blank.size(), false);
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            if (!table[i][j] || chk[i][j]) continue;
            vector<pii> block;
            queue<pii> q;
            block.push_back({0, 0});
            q.push({i, j});
            chk[i][j] = 1;
            while (!q.empty()){
                pii h = q.front(); q.pop();
                for (int k = 0; k < 4; k++){
                    int y = h.first + dy[k];
                    int x = h.second + dx[k];
                    if (x < 0 || y < 0 || x == M || y == N) continue;
                    if (!table[y][x] || chk[y][x]) continue;
                    chk[y][x] = 1;
                    block.push_back({y - i, x - j});
                    q.push({y, x});
                }
            }
            
            for (int k = 0; k < blank.size(); k++){
                if (is_filled[k] || (blank[k].size() != block.size())) continue;
                bool flag = 0;
                for (int l = 0; l < 4; l++){
                    if (is_same_shape(blank[k], block)){
                        is_filled[k] = 1;
                        answer += block.size();
                        flag = 1;
                        break;
                    }    
                    rotate_block(block);
                }
                if (flag) break;
            }
        }
    }
    return answer;
}

int main(){
    int N, M;
    cin >> N >> M;
    vector<vector<int>> game_board(N, vector<int>(M, 0)), table(N, vector<int>(M, 0));
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            cin >> game_board[i][j];
        }  
    }
    for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) cin >> table[i][j];

    cout << solution(game_board, table);



    return 0;
}