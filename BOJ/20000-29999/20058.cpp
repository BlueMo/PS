#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
using namespace std;
typedef pair<int, int> CRDNT;

int N, Q, L, sum, max_group_size;
vector<vector<int>> A;

vector<vector<int>> rotate_map(int L){
    vector<vector<int>> ret(N, vector<int>(N, 0));
    L = pow(2, L);
    int cnt = N / L, dy, dx;
    for (int i = 0; i < cnt; i++){
        for (int j = 0; j < cnt; j++){
            dy = i * L, dx = j * L;
            for (int y = 0; y < L; y++){
                for (int x = 0; x < L; x++){
                    ret[y + dy][x + dx] = A[L - x + dy - 1][y + dx];    
                }
            }
        }
    }
    return ret;
}

vector<vector<int>> reduce_ice(){
    vector<vector<int>> ret(N, vector<int>(N, 0));
    for (int y = 0; y < N; y++){
        for (int x = 0; x < N; x++){
            int cnt = 0;
            ret[y][x] = A[y][x];
            if (!A[y][x]) continue;
            for (int k = 0; k < 4; k++){
                int ny = y + "2011"[k] - '1';
                int nx = x + "1120"[k] - '1';
                if (ny < 0 || nx < 0 || ny == N || nx == N) continue;
                if (A[ny][nx]) cnt++;
            }
            if (cnt < 3) ret[y][x]--;
        }
    }
    return ret;
}

void calc_ans(){
    vector<vector<bool>> chk(N, vector<bool>(N, false));
    int group_size = 0;

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            sum += A[i][j];
            if (!A[i][j] || chk[i][j]) continue;
            queue<CRDNT> q;
            group_size = 0;
            chk[i][j] = 1;
            q.push({i, j});
            while (!q.empty()){
                auto [y, x] = q.front(); q.pop();
                group_size++;
                for (int k = 0; k < 4; k++){
                    int ny = y + "2011"[k] - '1';
                    int nx = x + "1120"[k] - '1';
                    if (ny < 0 || nx < 0 || ny == N || nx == N) continue;
                    if (A[ny][nx] && !chk[ny][nx]){
                        chk[ny][nx] = 1;
                        q.push({ny, nx});
                    }
                }
            }
            max_group_size = max(max_group_size, group_size);
        }
    }
}

void print_map(){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++) cout << A[i][j] << " ";
        cout << endl;
    }cout << endl;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> N >> Q;
    N = pow(2, N);
    A.resize(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) cin >> A[i][j];
    while (Q--){
        cin >> L;
        A = rotate_map(L);
        //print_map();
        A = reduce_ice();
        //print_map();
    }
    calc_ans();
    cout << sum << "\n" << max_group_size;
    return 0;
}