#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
typedef pair<int, int> pii;

#define MAX_N 1001
#define INF 0x7fffffff;

int N, M, X, dist[MAX_N], dist2[MAX_N], u, v, t, ans;
vector<pii> adj[MAX_N], adj2[MAX_N];
priority_queue<pii, vector<pii>, greater<pii>> pq;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> N >> M >> X;
    for (int i = 0; i < M; i++){
        cin >> u >> v >> t;
        adj[u].push_back({t, v});
        adj2[v].push_back({t, u});
    }
    for (int i = 1; i <= N; i++){
        dist[i] = dist2[i] = INF;
    }

    dist[X] = 0;
    pq.push({0, X});
    while (!pq.empty()){
        auto [cost, cur] = pq.top(); pq.pop();
        if (dist[cur] < cost) continue;

        for (auto [c, next] : adj[cur]){
            int newCost = cost + c;
            if (dist[next] <= newCost) continue;
            dist[next] = newCost;
            pq.push({newCost, next});
        }
    }

    pq = {};
    dist2[X] = 0;
    pq.push({0, X});
    while (!pq.empty()){
        auto [cost, cur] = pq.top(); pq.pop();
        if (dist2[cur] < cost) continue;

        for (auto [c, next] : adj2[cur]){
            int newCost = cost + c;
            if (dist2[next] <= newCost) continue;
            dist2[next] = newCost;
            pq.push({newCost, next});
        }
    }

    for (int i = 1; i <= N; i++){
        ans = max(ans, dist[i] + dist2[i]);
    }
    cout << ans;
    return 0;
}