// SPFA

#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#define INF 0x7fffffff
using namespace std;
typedef pair<int, int> pii;

int N, M, A, B, C, cnt[501];
long long dist[501];
bool chk[501];
vector<pii> adj[501];
queue<pii> q;
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> N >> M;
    for (int i = 0; i < M; ++i){
        cin >> A >> B >> C;
        adj[A].push_back({C, B});
    }
    for (int i = 1; i <= N; ++i) dist[i] = INF;
    
    q.push({0, 1});
    dist[1] = 0;
    while (!q.empty()){
        pii h = q.front();
        if (h.first == N){
            cout << "-1";
            return 0;
        }
        q.pop();
        chk[h.second] = 0;

        for (auto &i : adj[h.second]){
            long long newDist = dist[h.second] + i.first;
            if (dist[i.second] <= newDist) continue;
            dist[i.second] = newDist;
            if (!chk[i.second]){
                chk[i.second] = 1;
                q.push({h.first + 1, i.second});
            }
        }
    }
    for (int i = 2; i <= N; ++i){
        if (dist[i] != INF) cout << dist[i] << "\n";
        else cout << "-1\n";
    }
    return 0;
}