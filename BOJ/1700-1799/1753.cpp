#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
typedef pair<int, int> pii;

int V, E, K, u, v, w;
int chk[20001];
vector<pii> adj[20001];
priority_queue<pii, vector<pii>> pq;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> V >> E >> K;
    for (int i = 0; i < E; ++i){
        cin >> u >> v >> w;
        adj[u].push_back({w, v});
    }
    for (int i = 1; i <= V; ++i) chk[i] = -987654321;
    pq.push({0, K});
    chk[K] = 0;
    while (!pq.empty()){
        pii h = pq.top();
        pq.pop();
        if(chk[h.second] > h.first) continue;
        
        for (auto &i : adj[h.second]){
            int d = h.first - i.first;
            if (chk[i.second] < d){
                pq.push({d, i.second});
                chk[i.second] = d;
            }
        }
    }

    for (int i = 1; i <= V; ++i){
        if (chk[i] == -987654321) cout << "INF\n";
        else cout << -chk[i] << "\n";
    }
}