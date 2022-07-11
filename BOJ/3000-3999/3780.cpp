#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

#define MAX_N 20001
int T, N, u, v, par[MAX_N], dist[MAX_N];
char ch;

int findParent(int u){
    if (u == par[u]) return u;
    int p = findParent(par[u]);
    dist[u] += dist[par[u]];
    return par[u] = p;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T--){
        cin >> N;
        for (int i = 1; i <= N; i++){
            par[i] = i;
        }
        memset(dist, 0, sizeof(dist));
        while (1){
            cin >> ch;
            if (ch == 'O') break;
            else if (ch == 'E'){
                cin >> u;
                findParent(u);
                cout << dist[u] << "\n";
            }
            else {
                cin >> u >> v;
                // u is already root node (center)
                dist[u] = abs(u - v) % 1000;
                par[u] = v;
            }
        }
    }

    return 0;
}