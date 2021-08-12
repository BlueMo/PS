#include<iostream>
#include<algorithm>
#include<queue>
#include<cstring>
#include<vector>
using namespace std;
typedef pair<int, int> pii;

int N, M, S, D, u, v, p, dist[501];
bool chk[501];
vector<pii> adj[501], path[501];
priority_queue<pii, vector<pii>, greater<pii>> pq;
queue<int> q;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    while(1){
        cin >> N >> M;
        if (!N && !M) break;
        cin >> S >> D;
        for (int i = 0; i < N; i++) dist[i] = 0x7fffffff;
        for (int i = 0; i < M; i++){
            cin >> u >> v >> p;
            adj[u].push_back({p, v});
        }
        pq.push({0, S});
        dist[S] = 0;

        while (!pq.empty()){
            int cost = pq.top().first;
            int cur = pq.top().second;
            pq.pop();
            if (cost > dist[cur]) continue;

            for (auto &i : adj[cur]){
                int nextCost = cost + i.first;
                int next = i.second;

                if (nextCost < dist[next]){
                    dist[next] = nextCost;
                    path[next].clear();
                    path[next].push_back({i.first, cur});
                    pq.push({nextCost, next});
                }
                else if (nextCost == dist[next]) path[next].push_back({i.first, cur});
            }
        }
        q.push(D);
        while (!q.empty()){
            int h = q.front();
            q.pop();
            if (chk[h]) continue;
            chk[h] = 1;

            for (auto &i : path[h]){
                q.push(i.second);

                for (auto &j : adj[i.second]){
                    if (j.first == i.first && j.second == h){
                        j.first = 0x7fffffff; 
                    } 
                }
            }
        }

        for (int i = 0; i < N; i++) dist[i] = 0x7fffffff;
        pq.push({0, S});
        dist[S] = 0;

        while (!pq.empty()){
            int cost = pq.top().first;
            int cur = pq.top().second;
            pq.pop();
            if (cost > dist[cur]) continue;

            for (auto &i : adj[cur]){
                if (i.first == 0x7fffffff) continue;
                int nextCost = cost + i.first;
                int next = i.second;

                if (nextCost < dist[next]){
                    dist[next] = nextCost;
                    pq.push({nextCost, next});
                }
            }
        }

        if (dist[D] == 0x7fffffff) cout << "-1\n";
        else cout << dist[D] << "\n";

        for (int i = 0; i < N; i++){
            adj[i].clear();
            path[i].clear();
            chk[i] = 0;
        }
    }
    return 0;
}