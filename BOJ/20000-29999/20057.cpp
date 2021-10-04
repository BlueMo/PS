#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <tuple>
using namespace std;
typedef tuple<int, int, double> i2d1tuple;
typedef pair<int, int> crdnt;

const i2d1tuple SAND_RATE[9] = {
    {-2, 0, 0.02},
    {-1, -1, 0.10}, {-1, 0, 0.07}, {-1, 1, 0.01},
    {0, -2, 0.05},
    {1, -1, 0.10}, {1, 0, 0.07}, {1, 1, 0.01},
    {2, 0, 0.02}
};
const crdnt DIR_CRDNT[4] = { {0, -1}, {1, 0}, {0, 1}, {-1, 0}}; 
i2d1tuple dir_sand_rate[4][9];
int N, out_sand;
vector<vector<int>> sand_map;

void init_sand_rate(i2d1tuple arr[], i2d1tuple* ret){
    for (int i = 0; i < 9; i++){
        auto [y, x, rate] = arr[i];
        ret[i] = {-x, y, rate};
    }
}

void move_sand(int y, int x, int dir){
    int remain_sand = sand_map[y][x];
    for (auto [dy, dx, rate] : dir_sand_rate[dir]){
        int ny = y + dy, nx = x + dx;
        int sand = sand_map[y][x] * rate;
        if (ny < 0 || nx < 0 || ny >= N || nx >= N) out_sand += sand;
        else sand_map[ny][nx] += sand;   
        remain_sand -= sand;
    }
    sand_map[y][x] = 0;
    y += DIR_CRDNT[dir].first, x += DIR_CRDNT[dir].second;
    if (y < 0 || x < 0 || y >= N || x >= N) out_sand += remain_sand;
    else sand_map[y][x] += remain_sand;
}

void print_sand_map(){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            cout << sand_map[i][j] << " ";
        }cout << endl;
    }cout << endl;
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    // init dir_sand_rate[]
    for (int i = 0; i < 9; i++) dir_sand_rate[0][i] = SAND_RATE[i];
    for (int i = 1; i < 4; i++) init_sand_rate(dir_sand_rate[i-1], dir_sand_rate[i]);
    
    cin >> N;
    sand_map.assign(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            int t; cin >> t;
            sand_map[i][j] = t;
        }
    }

    int y = N/2, x = N/2, flag = 0, cnt = 1, dir = 0;
    while (1){
        for (int i = 0; i < cnt; i++){
            y += DIR_CRDNT[dir].first, x += DIR_CRDNT[dir].second;
            if (y == 0 && x == -1) break;
            move_sand(y, x, dir);
            //print_sand_map();
        }
        if (y == 0 && x == -1) break;
        flag++;
        dir = (dir+1) % 4;
        if (flag == 2){
            flag = 0;
            cnt++;
        }
    }

    cout << out_sand;
    return 0;
}