#include <iostream>
#include <vector>
#include <algorithm>
#define INF 1000000000
using namespace std;
typedef pair<int, int> pii;

int N, stCity, enCity, M, u, v, w, money[1001];
long long dist[1001];
vector<pii> adj[1001];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> N >> stCity >> enCity >> M;
    for (int i = 0; i < M; ++i){
        cin >> u >> v >> w;
        adj[u].push_back({w, v});
    }
    for (int i = 0; i < N; ++i){
        cin >> money[i];
        dist[i] = 2*INF;
    }
    for (int i = 0; i < N; ++i) for (auto &j : adj[i]) j.first -= money[j.second];

    dist[stCity] = -money[stCity];
    for (int k = 1; k <= 2*N; ++k){
        for (int i = 0; i < N; ++i){
            if (dist[i] == 2*INF) continue;
            for (auto &j : adj[i]){
                if (dist[i] == INF){
                    dist[j.second] = INF;
                    continue;
                }
                if (dist[i] + j.first >= dist[j.second]) continue;
                dist[j.second] = dist[i] + j.first;
                if (k >= N) dist[j.second] = INF;
            }
        }
    }

    if (dist[enCity] == 2*INF) cout << "gg";
    else if (dist[enCity] == INF) cout << "Gee";
    else cout << -dist[enCity];

    return 0;
}