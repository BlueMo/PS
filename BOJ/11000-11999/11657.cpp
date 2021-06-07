#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#define INF 0x7fffffff
using namespace std;
typedef pair<int, int> pii;

int N, M, a, b, c;
long long dist[501];
vector<pii> adj[501];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> N >> M;
    for (int i = 0; i < M; ++i){
        cin >> a >> b >> c;
        adj[a].push_back({c, b});
    }
    for (int i = 1; i <= N; ++i) dist[i] = INF;
    dist[1] = 0;

    for (int k = 1; k <= N; ++k){
        for (int i = 1; i <= N; ++i){
            if (dist[i] == INF) continue;
            for (auto &j : adj[i]){
                if (dist[j.second] > dist[i] + j.first){
                    dist[j.second] = dist[i] + j.first;
                    if (k == N){
                        cout << "-1";
                        return 0;
                    }
                }
            }
        }
    }

    for (int i = 2; i <= N; ++i){
        if (dist[i] == INF) cout << "-1\n";
        else cout << dist[i] << "\n";
    }
    return 0;
}