#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
typedef pair<long long, int> pii;

int n, m, k, a, b, c;
vector<pii> adj[1001];
priority_queue<long long> dist[1001];
priority_queue<pii, vector<pii>, greater<pii>> pq;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m >> k;
    for (int i = 0; i < m; i++){
        cin >> a >> b >> c;
        adj[a].push_back({c, b});
    }
    pq.push({0, 1});
    dist[1].push(0);        // fail1

    while (!pq.empty()){
        pii cur = pq.top();
        pq.pop();

        for (auto &next : adj[cur.second]){
            long long d = cur.first + next.first;

            if (dist[next.second].size() < k){
                dist[next.second].push(d);
                pq.push({d, next.second});
            }
            else if (dist[next.second].top() > d){
                dist[next.second].pop();
                dist[next.second].push(d);
                pq.push({d, next.second});
            }
        }
    }

    for (int i = 1; i <= n; i++){
        if (dist[i].size() < k) cout << "-1\n";
        else cout << dist[i].top() << "\n";
    }
    return 0;
}

