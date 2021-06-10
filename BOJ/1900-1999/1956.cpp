#include <iostream>
#include <algorithm>
#define INF 987654321
using namespace std;

int V, E, a, b, c, dist[401][401], ans;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> V >> E;
    for (int i = 1; i <= V; ++i){
        for (int j = 1; j <= V; ++j){
            if (i != j) dist[i][j] = INF;
        }
    }
    for (int i = 0; i < E; ++i){
        cin >> a >> b >> c;
        dist[a][b] = c;
    }
    for (int k = 1; k <= V; ++k){
        for (int i = 1; i <= V; ++i){
            for (int j = 1; j <= V; ++j){
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    ans = INF;
    for (int i = 1; i <= V; ++i){
        for (int j = 1; j <= V; ++j){
            if (i == j) continue;
            ans = min(ans, dist[i][j] + dist[j][i]);
        }
    }
    if (ans == INF) cout << -1;
    else cout << ans;

    return 0;
}