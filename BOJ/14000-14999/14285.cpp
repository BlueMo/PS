#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
typedef pair<int, int> pii;

struct D{
    int distSum, maxCost, v;

    bool operator > (const D &a)const{
        return distSum - maxCost > a.distSum - a.maxCost;
    }
};

int n, m, a, b, c, s, t, dist[5001], ans;
vector<pii> adj[5001];
priority_queue<D, vector<D>, greater<D>> pq;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 0; i < m; i++){
        cin >> a >> b >> c;
        ans += c;
        adj[a].push_back({c, b});
        adj[b].push_back({c, a});
    }   
    cin >> s >> t;
    for (int i = 1; i <= n; i++) dist[i] = 0x7fffffff;
    
    dist[s] = 0;
    pq.push({0, 0, s});
    while (!pq.empty()){
        int cur = pq.top().v;
        int maxCost = pq.top().maxCost;
        int distSum = pq.top().distSum;
        pq.pop();
        if (distSum - maxCost > dist[cur]) continue;

        for (auto &i : adj[cur]){
            int next = i.second;
            int newDistSum = distSum + i.first;
            int newMaxCost = max(maxCost, i.first);

            if (newDistSum - newMaxCost < dist[next]){
                dist[next] = newDistSum - newMaxCost;
                pq.push({newDistSum, newMaxCost, next});
            }
        }
    }

    cout << ans - dist[t];
    return 0;
}