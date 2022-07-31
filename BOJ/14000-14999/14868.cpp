#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
typedef pair<int, int> pii;

int N, K, x, y, ans;
int m[2002][2002], par[100001];
int dy[4] = {-1, 1, 0, 0}, dx[4] = {0, 0, -1, 1};
queue<pii> q, q2;

int findParent(int u){
    if (u == par[u]) return u;
    return par[u] = findParent(par[u]);
}

void unionSet(int u, int v){
    u = findParent(u), v = findParent(v);

    if (u != v){
        K--;
        par[v] = u;
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> N >> K;
    for (int i = 1; i <= K; i++){
        cin >> x >> y;
        m[y][x] = i;
        par[i] = i;
        q.push({y, x});
    }

    while (1){
        while (!q.empty()){
            auto [y, x] = q.front(); q.pop();
            q2.push({y, x});

            for (int i = 0; i < 4; i++){
                int ny = y + dy[i], nx = x + dx[i];

                if (ny == 0 || nx == 0 || ny > N || nx > N) continue;
                if (m[ny][nx] == 0) continue;
                
                unionSet(m[y][x], m[ny][nx]);
            }
        }

        if (K == 1) break;

        while (!q2.empty()){
            auto [y, x] = q2.front(); q2.pop();

            for (int i = 0; i < 4; i++){
                int ny = y + dy[i], nx = x + dx[i];

                if (ny == 0 || nx == 0 || ny > N || nx > N) continue;
                if (m[ny][nx] != 0) continue;

                m[ny][nx] = m[y][x];
                q.push({ny, nx});
            }
        }

        ans++;
    }

    cout << ans;

    return 0;
}