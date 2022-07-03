#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

typedef pair<int, int> pii;

#define MAX_N 10001

int n, u, v, c, dist[MAX_N];
pii maxNode;
bool chk[MAX_N];
vector<pii> tree[MAX_N];

void dfs(int p){
    for (auto [next, cost] : tree[p]){
        if (chk[next]) continue;
        chk[next] = 1;
        dist[next] = dist[p] + cost;
        if (dist[next] > maxNode.first){
            maxNode = {dist[next], next};
        }
        dfs(next);
    }
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 0; i < n - 1; i++){
        cin >> u >> v >> c;
        tree[u].push_back({v, c});
        tree[v].push_back({u, c});
    }
    chk[1] = 1;
    dfs(1);
    u = maxNode.second;
    memset(dist, 0, sizeof(int) * (n + 1));
    memset(chk, 0, sizeof(bool) * (n + 1));
    maxNode.first = 0;
    
    chk[u] = 1;
    dfs(u);

    cout << maxNode.first;
    return 0;
}