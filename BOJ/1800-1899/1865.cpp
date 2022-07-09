#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef pair<int, int> pii;

#define MAX_N 501
int TC, N, M, W, S, E, T, dist[MAX_N];
vector<pii> adj[MAX_N];
bool ans_flag;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> TC;

    while (TC--){
        cin >> N >> M >> W;
        ans_flag = 0;

        for (int i = 0; i < M; i++){
            cin >> S >> E >> T;
            adj[S].push_back({E, T});
            adj[E].push_back({S, T});
        }
        for (int i = 0; i < W; i++){
            cin >> S >> E >> T;
            adj[S].push_back({E, -T});
        }

        for (int k = 1; k <= N; k++){
            for (int i = 1; i <= N; i++){
                for (auto [j, w] : adj[i]){
                    if (dist[j] > dist[i] + w){
                        dist[j] = dist[i] + w;
                        if (k == N) ans_flag = 1;
                    }
                }
            }
        } 

        if (ans_flag) cout << "YES\n";
        else cout << "NO\n";
        for (int i = 0; i <= N; i++){
            adj[i].clear();
            dist[i] = 0;
        }
    }

    return 0;
}