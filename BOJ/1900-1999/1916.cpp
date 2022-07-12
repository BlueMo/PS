#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
typedef pair<int, int> pii;

#define MAX_N 1001
#define INF 0x7fffffff

int N, M, dist[MAX_N], a, b, t;
vector<pii> adj[MAX_N];
priority_queue<pii, vector<pii>, greater<pii>> pq;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> N >> M;
    for (int i = 1; i <= N; i++) dist[i] = INF;
    for (int i = 0; i < M; i++){
        cin >> a >> b >> t;
        adj[a].push_back({t, b}); 
    }
    cin >> a >> b;
    
    dist[a] = 0;
    pq.push({0, a});
    while (!pq.empty()){
        auto [cost, cur] = pq.top(); pq.pop();
        if (dist[cur] < cost) continue;

        for (auto [c, next] : adj[cur]){
            int newCost = cost + c;
            if (newCost >= dist[next]) continue;
            dist[next] = newCost;
            pq.push({newCost, next});
        }
    }

    cout << dist[b];
    return 0;
}