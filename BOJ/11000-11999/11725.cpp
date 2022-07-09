#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MAX_N (100001)

int N, a, b, p[MAX_N];
vector<int> adj[MAX_N];

void dfs(int par, int cur){
    for (auto i : adj[cur]){
        if (par == i) continue;
        p[i] = cur;
        dfs(cur, i);
    }
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    
    cin >> N;
    for (int i = 0; i < N - 1; i++){
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(0, 1);

    for (int i = 2; i <= N; i++){
        cout << p[i] << "\n";
    }
    return 0;
}