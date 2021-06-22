#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
typedef pair<long long, int> pli;
typedef pair<pair<long long, int>, int> plii;

int N, M, K, u, v, w;
vector<pli> adj[10001];
long long dist[10001][21], ans = 1e11;
priority_queue<plii, vector<plii>, greater<plii>> pq;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> N >> M >> K;
    for (int i = 0; i < M; ++i){
        cin >> u >> v >> w;
        adj[u].push_back({w, v});
        adj[v].push_back({w, u});
    }
    for (int i = 1; i <= N; ++i) for (int j = 0; j <= K; ++j) dist[i][j] = 1e11;
    
    pq.push({{0, 0}, 1});
    while (!pq.empty()){
        plii cur = pq.top(); pq.pop();

        if (cur.first.first > dist[cur.second][cur.first.second]) continue;         // fail1: TLE
        
        for (auto &i : adj[cur.second]){
            int next = i.second;

            if (dist[next][cur.first.second] > cur.first.first + i.first){
                dist[next][cur.first.second] = cur.first.first + i.first;
                pq.push({{dist[next][cur.first.second], cur.first.second}, next});
            }
            if (dist[next][cur.first.second + 1] > cur.first.first && cur.first.second < K){
                dist[next][cur.first.second + 1] = cur.first.first;
                pq.push({{dist[next][cur.first.second + 1], cur.first.second + 1}, next});
            }

            for (int j = cur.first.second + 1; j <= K; ++j){
                if (dist[next][j] < dist[next][cur.first.second]) break;
                dist[next][j] = dist[next][cur.first.second];
            }
        }
    }

    for (int i = 0; i <= K; ++i) ans = min(ans, dist[N][i]);
    cout << ans;
    return 0;
}