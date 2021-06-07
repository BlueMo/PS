#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int, int> pii;

int T, n, m, t, s, g, h, a, b, d, tmp, cost[2001];
vector<pii> adj[2001];
bool chk[2001];
priority_queue<pii> pq;
priority_queue<int, vector<int>, greater<int>> destiny;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> T;
    while (T--){
        cin >> n >> m >> t;
        cin >> s >> g >> h;
        for (int i = 1; i <= n; ++i){
            cost[i] = -0x7fffffff;
            chk[i] = 0;
            adj[i].clear();
        }
        for (int i = 0; i < m; ++i){
            cin >> a >> b >> d;
            adj[a].push_back({-d, b});
            adj[b].push_back({-d, a});
        }
        for (int i = 0; i < t; ++i){
            cin >> tmp;
            destiny.push(tmp);
        }
        pq.push({0, s});
        while (!pq.empty()){
            pii head = pq.top();
            pq.pop();

            for (auto &i : adj[head.second]){
                int dist = head.first + i.first;

                if (dist < cost[i.second]) continue;
                if (dist > cost[i.second]){
                    chk[i.second] = 0;          // fail point
                    cost[i.second] = dist;
                    pq.push({dist, i.second});
                }
                if (chk[head.second] && dist == cost[i.second]) chk[i.second] = 1;
                if ((i.second == g && head.second == h) || (i.second == h && head.second == g)) chk[i.second] = 1;
            }
        }

        for (int i = 1; i <= n, !destiny.empty(); ++i)
        {
            if (destiny.top() == i){
                if (chk[i]) cout << i << " ";
                destiny.pop();
            }
        }
        cout << "\n";
    }

    return 0;
}