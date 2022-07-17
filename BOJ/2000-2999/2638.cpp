#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
typedef pair<int, int> pii;

#define MAX_SIZE 101

int N, M, table[MAX_SIZE][MAX_SIZE], chkIdx = 1;
int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
queue<pii> cheese, q;

void findAir(){
    q.push({0, 0});
    table[0][0] = ++chkIdx;

    while (!q.empty()){
        auto [y, x] = q.front(); q.pop();

        for (int i = 0; i < 4; i++){
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < 0 || ny < 0 || nx == M || ny == N) continue;
            if (table[ny][nx] == chkIdx || table[ny][nx] == 1) continue;
            table[ny][nx] = chkIdx;
            q.push({ny, nx});
        }
    }
}

void chkCheese(){
    int n = cheese.size(), cnt;
    for (int i = 0; i < n; i++){
        auto [y, x] = cheese.front(); cheese.pop();
        cnt = 0;
        for (int j = 0; j < 4; j++){
            int nx = x + dx[j], ny = y + dy[j];
            if (nx < 0 || ny < 0 || nx == M || ny == N) continue;
            if (table[ny][nx] == chkIdx) cnt++;
        }
        if (cnt < 2) cheese.push({y, x});
        else table[y][x] = 0;
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> N >> M;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            cin >> table[i][j];
            if (table[i][j]) cheese.push({i, j});
        }
    }

    for (int i = 1; ; i++){
        findAir();
        chkCheese();
        if (!cheese.size()){
            cout << i;
            break;
        }
    }
    

    return 0;
}