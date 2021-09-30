#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
typedef pair<int, int> CRDNT;

int N, M, answer;
vector<vector<int>> game_map;

vector<CRDNT> find_max_group(){
    vector<vector<int>> chk(N, vector<int>(N, 0));

    vector<CRDNT> max_group;
    CRDNT ref_crdnt = {-1, -1};
    int group_num = 0, max_rainbow = 0;

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (chk[i][j] || game_map[i][j] < 1) continue;
            int color = game_map[i][j], cnt_rainbow = 0;
            vector<CRDNT> group;
            CRDNT min_crdnt = {i, j}; 
            int head = 0;
            group_num++;
            group.push_back({i, j});
            chk[i][j] = 1;
            while (head < group.size()){
                auto [y, x] = group[head++];

                for (int k = 0; k < 4; k++){
                    int ny = y + "2011"[k] - '1';
                    int nx = x + "1102"[k] - '1';
                    if (nx < 0 || ny < 0 || nx == N || ny == N) continue;
                    if (game_map[ny][nx] == color && !chk[ny][nx]){
                        chk[ny][nx] = 1;
                        group.push_back({ny, nx});
                        if (ny < min_crdnt.first) min_crdnt = {ny, nx};
                        else if (ny == min_crdnt.first && nx < min_crdnt.first) min_crdnt.second = nx;
                    }
                    else if (!game_map[ny][nx] && chk[ny][nx] != group_num){
                        cnt_rainbow++;
                        chk[ny][nx] = group_num;
                        group.push_back({ny, nx});
                    }
                }
            }
            if (group.size() < 2) continue;
            if (group.size() > max_group.size()){
                max_group = group;
                ref_crdnt = min_crdnt;
                max_rainbow = cnt_rainbow;
            }
            else if (group.size() == max_group.size()){
                if (cnt_rainbow > max_rainbow){
                    max_group = group;
                    ref_crdnt = min_crdnt;
                    max_rainbow = cnt_rainbow;
                }
                else if (cnt_rainbow == max_rainbow){
                    if (min_crdnt.first > ref_crdnt.first){
                        max_group = group;
                        ref_crdnt = min_crdnt;
                        max_rainbow = cnt_rainbow;
                    }
                    else if (min_crdnt.first == ref_crdnt.first && min_crdnt.second > ref_crdnt.second){
                        max_group = group;
                        ref_crdnt = min_crdnt;
                        max_rainbow = cnt_rainbow;
                    }
                }
            }
        }
    }
    return max_group;
}

void apply_gravity(){
    for (int i = 0; i < N; i++){
        int j = 0;
        stack<int> s;
        while (j < N){
            while (j < N && game_map[j][i] != -1){
                if (game_map[j][i] >= 0){
                    s.push(game_map[j][i]);
                    game_map[j][i] = -2;
                }
                j++;
            }
            int k = j - 1;
            while (!s.empty()){
                int color = s.top(); s.pop();
                game_map[k--][i] = color;
            }
            j++;
        }
    }
}

void rotate_map(){
    vector<vector<int>> tmp_map(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) tmp_map[N-1-j][i] = game_map[i][j];
    game_map = tmp_map;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> N >> M;
    game_map.assign(N, vector<int>(N, 0));
    
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            int color;
            cin >> color;
            game_map[i][j] = color;
        }
    }

    while (1){
        vector<CRDNT> max_group = find_max_group();
        if (!max_group.size()) break;
        answer += max_group.size() * max_group.size();
        for (auto [y, x] : max_group) game_map[y][x] = -2;       // Erase block group

        apply_gravity();
        rotate_map();
        apply_gravity();
    }
    cout << answer;
    return 0;
}