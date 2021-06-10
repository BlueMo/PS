#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <queue>
#define INF 0x7fffffff
using namespace std;

struct Ticket{
    int d, c, p;
};
int T, N, M, K, u, v, c, d, dist[101][10001], ans;
vector<Ticket> adj[101];
queue<Ticket> q;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;

    while (T--){
        cin >> N >> M >> K;
        for (int i = 0; i < K; ++i){
            cin >> u >> v >> c >> d;
            adj[u].push_back({d, c, v});
        }
        for (int i = 1; i <= N; ++i){
            for (int j = 0; j <= M; ++j){
                dist[i][j] = INF;
            }
        }
        dist[1][0] = 0;
        q.push({0, 0, 1});

        while (!q.empty()){
            Ticket h = q.front();
            q.pop();

            if (h.d > dist[h.p][h.c]) continue;
            
            for (auto &i : adj[h.p]){
                int newCost = h.c + i.c;
                if (newCost > M) continue;
                int newDist = h.d + i.d;
                if (newDist >= dist[i.p][newCost]) continue;

                for (int j = newCost; j <= M; ++j){
                    if (dist[i.p][j] > newDist) dist[i.p][j] = newDist;
                    else break;
                }
                q.push({newDist, newCost, i.p});
            }
        }
        ans = dist[N][M];
        if (ans != INF) cout << ans << "\n";
        else cout << "Poor KCM\n";
        for (int i = 1; i <= N; ++i) adj[i].clear();
    }
    return 0;
}