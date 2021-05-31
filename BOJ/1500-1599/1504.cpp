#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
#define INF 123456789
typedef pair<int, int> pii;

int N, E, a, b, c, dis[801], r[2];
vector<pii> adj[801];
priority_queue<pii> pq;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N >> E;
    for (int i = 1; i <= N; ++i) dis[i] = -INF;
    for (int i = 0; i < E; ++i){
        cin >> a >> b >> c;
        adj[a].push_back({c, b});
        adj[b].push_back({c, a});
    }
    cin >> a >> b;

    dis[1] = 0;
    pq.push({0, 1});
    while (!pq.empty()){
        pii h = pq.top();
        pq.pop();

        for (auto &i : adj[h.second]){
            int d = h.first - i.first;

            if (dis[i.second] < d){
                dis[i.second] = d;
                pq.push({d, i.second});
            }
        }
    }
    r[0] = -dis[a];
    r[1] = -dis[b];
    for (int i = 1; i <= N; ++i) dis[i] = -INF;
    
    dis[a] = 0;
    pq.push({0, a});
    while (!pq.empty()){
        pii h = pq.top();
        pq.pop();

        for (auto &i : adj[h.second]){
            int d = h.first - i.first;

            if (dis[i.second] < d){
                dis[i.second] = d;
                pq.push({d, i.second});
            }
        }
    }
    r[0] -= dis[b];
    r[1] -= dis[N];
    for (int i = 1; i <= N; ++i) dis[i] = -INF;
    
    dis[b] = 0;
    pq.push({0, b});
    while (!pq.empty()){
        pii h = pq.top();
        pq.pop();

        for (auto &i : adj[h.second]){
            int d = h.first - i.first;

            if (dis[i.second] < d){
                dis[i.second] = d;
                pq.push({d, i.second});
            }
        }
    }
    r[0] -= dis[N];
    r[1] -= dis[a];

    r[0] = r[0] < INF ? r[0] : INF;
    r[1] = r[1] < INF ? r[1] : INF;
    r[0] = min(r[0], r[1]);

    if (r[0] == INF) cout << "-1";
    else cout << r[0];
    return 0;
}