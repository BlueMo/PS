#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
typedef pair<int, int> pii;

#define MAX_V 100001

int V, u, v, w;
vector<pii> adj[MAX_V];
pii maxNode;

void dfs(int par, int cur, int dist){
    for (auto [next, cost] : adj[cur]){
        if (par == next) continue;
        if (dist + cost > maxNode.first){
            maxNode = {dist + cost, next};
        }
        dfs(cur, next, dist + cost);
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> V;
    for (int i = 0; i < V; i++){
        cin >> u;
        while (1){
            cin >> v;
            if (v == -1) break;
            cin >> w;
            adj[u].push_back({v, w}); 
        }
    }
    dfs(0, 1, 0);
    u = maxNode.second;
    maxNode = {0, 0};

    dfs(0, u, 0);
    cout << maxNode.first;
    return 0;
}