#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef pair<int, int> pii;
typedef pair<int, pair<int, int>> piii;
typedef long long ll;

#define MAX_M   (100001)
#define MAX_N   (100001)

const int MOD = 1e9;
int N, M, x, y, w, par[MAX_N], cnt[MAX_N];
ll ans, totalCost;
piii edge[MAX_M];

int findParent(int u){
    if (par[u] == u) return u;
    return par[u] = findParent(par[u]);
}
void unionGroup(int u, int v){
    if (cnt[u] < cnt[v]) swap(u, v);
    par[v] = u;
    cnt[u] += cnt[v];
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    
    cin >> N >> M;

    for (int i = 0; i < M; i++){
        cin >> x >> y >> w;

        totalCost += w;
        edge[i] = {w, {x, y}};
    }
    sort(edge, edge + M, [&](piii a, piii b){ return a.first > b.first; });
    
    for (int i = 1; i <= N; i++) par[i] = i, cnt[i] = 1;

    for (int i = 0; i < M; i++){
        x = edge[i].second.first, y = edge[i].second.second;

        x = findParent(x); y = findParent(y);

        if (x != y){
            ans = (ans + (((1LL * cnt[x] * cnt[y]) % MOD) * totalCost) % MOD) % MOD;
            unionGroup(x, y);
        }

        totalCost -= edge[i].first;
    }
    cout << ans;

    return 0;
}