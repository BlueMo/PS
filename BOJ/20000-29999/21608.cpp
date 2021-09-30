#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
#include <tuple>
using namespace std;
typedef pair<int, int> pii;
typedef tuple<int, int, int, int> tiiii;

int N, answer;
vector<int> order;
vector<vector<bool>> prefer;
vector<vector<int>> class_map;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> N;
    prefer.assign(N*N+1, vector<bool>(N*N+1, 0));
    class_map.assign(N, vector<int>(N, 0));
    for (int i = 0; i < N*N; i++){
        int a, b;
        cin >> a;
        order.push_back(a);
        for (int j = 0; j < 4; j++){
            cin >> b;
            prefer[a][b] = 1;
        }
    }

    class_map[1][1] = order[0];
    for (int i = 1; i < N*N; i++){
        int idx = order[i];
        priority_queue<tiiii> pq;
        for (int j = 0; j < N; j++){
            for (int k = 0; k < N; k++){
                if (class_map[j][k]) continue;
                int cnt_prefer = 0, cnt_blank = 0;
                for (int l = 0; l < 4; l++){
                    int y = j + "2011"[l] - '1';
                    int x = k + "1102"[l] - '1';
                    if (x < 0 || y < 0 || x == N || y == N) continue;
                    if (prefer[idx][class_map[y][x]]) cnt_prefer++;
                    else if(!class_map[y][x]) cnt_blank++;
                }
                pq.push({cnt_prefer, cnt_blank, -j, -k});
            }
        }
        auto [t1, t2, y, x] = pq.top();
        class_map[-y][-x] = idx;
    }

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (!class_map[i][j]) continue;
            int idx = class_map[i][j];
            int cnt_prefer = 0;
            for (int k = 0; k < 4; k++){
                int y = i + "2011"[k] - '1';
                int x = j + "1102"[k] - '1';
                if (y < 0 || x < 0 || y == N || x == N) continue;
                if (prefer[idx][class_map[y][x]]) cnt_prefer++;
            }
            if (cnt_prefer > 0) answer += pow(10, cnt_prefer-1);
        }
    }
    cout << answer;
    return 0;
}