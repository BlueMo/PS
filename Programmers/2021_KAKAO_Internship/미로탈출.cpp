#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <tuple>
#include <iostream>
using namespace std;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
const int INF = 0x7fffffff;

int solution(int n, int start, int end, vector<vector<int>> roads, vector<int> traps) {
    int answer = INF;
    priority_queue<tiii, vector<tiii>, greater<tiii>> pq;
    vector<vector<pii>> adj(n+1), radj(n+1);
    vector<vector<int>> min_cost(1024, vector<int>(n+1, INF));
    vector<int> chk_trap(n+1, 0);

    for (auto r : roads){
        adj[r[0]].push_back({r[2], r[1]});
        radj[r[1]].push_back({r[2], r[0]});
    }
    for (int i = 0; i < traps.size(); i++) chk_trap[traps[i]] = 1<<i;

    min_cost[0][start] = 0;
    pq.push({0, start, 0});
    while (!pq.empty()){
        auto [cost, cur, state] = pq.top(); pq.pop();
        
        if (cost > min_cost[state][cur]) continue;
        bool cur_flag = (state & chk_trap[cur]) > 0;
        
        for (auto [new_cost, next] : adj[cur]){
            bool next_flag = (state & chk_trap[next]) > 0;
            if (cur_flag ^ next_flag) continue;
            new_cost += cost;
            int new_state = state ^ chk_trap[next];
            if (new_cost < min_cost[new_state][next]){
                min_cost[new_state][next] = new_cost;
                pq.push({new_cost, next, new_state});
            }
        }
        
        for (auto [new_cost, next] : radj[cur]){
            bool next_flag = (state & chk_trap[next]) > 0;
            if (cur_flag ^ next_flag == 0) continue;
            new_cost += cost;
            int new_state = state ^ chk_trap[next];
            if (new_cost < min_cost[new_state][next]){
                min_cost[new_state][next] = new_cost;
                pq.push({new_cost, next, new_state});
            }
        }
    }
    
    for (int i = 0; i < 1024; i++) answer = min(answer, min_cost[i][end]);
    return answer;
}

int main(){
    int n, start, end, m, t;
    cin >> n >> start >> end;
    cin >> m >> t;
    vector<vector<int>> roads(m);
    vector<int> traps;

    for (int i = 0; i < m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        roads[i].push_back(u);
        roads[i].push_back(v);
        roads[i].push_back(w);
    }
    for (int i = 0; i < t; i++){
        int u;
        cin >> u;
        traps.push_back(u);
    }

    cout << solution(n, start, end, roads, traps);

    return 0;
}