#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

int K, V, E, u, v, chk[20001];
vector<int> adj[20001];
bool flag;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> K;
    while (K--){
        cin >> V >> E;
        for (int i = 0; i < E; ++i){
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        for (int i = 1; i <= V; ++i){
            if (chk[i]) continue;
            chk[i] = 1;
            queue<int> q;
            q.push(i);
            while (!q.empty() && !flag){
                int h = q.front();
                q.pop();
                
                for (auto &j : adj[h]){
                    if (chk[j]){
                        if (chk[h] == chk[j]){
                            flag = 1; break;
                        }
                        continue;
                    }
                    chk[j] = -chk[h];
                    q.push(j);
                }
            }
        }

        if (flag) cout << "NO\n";
        else cout << "YES\n";

        for (int i = 1; i <= V; ++i) adj[i].clear();
        memset(chk, 0, sizeof(chk));
        flag = 0;
    }
}