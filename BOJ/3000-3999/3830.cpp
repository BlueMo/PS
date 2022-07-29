#include <iostream>
#include <algorithm>
using namespace std;

#define MAX_N 100001

int N, M, a, b, w, d1, d2, p1, p2;
int par[MAX_N];
long long dist[MAX_N];
char ch;

int findParent(int u){
    if (u == par[u]) return u;
    int tmp = findParent(par[u]);
    dist[u] += dist[par[u]];
    return par[u] = tmp;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    while (1){
        cin >> N >> M;
        if (!N && !M) break;

        for (int i = 1; i <= N; i++){
            par[i] = i;
            dist[i] = 0LL;
        }
        while (M--){
            cin >> ch >> a >> b;
            if (ch == '!'){
                cin >> w;
                p1 = findParent(a);
                p2 = findParent(b);
                d1 = dist[a];
                d2 = dist[b];
                if (d1 > w + d2){
                    par[p2] = p1;
                    dist[p2] = d1 - w - d2;
                }
                else{
                    par[p1] = p2;
                    dist[p1] = w + d2 - d1;
                }
            }
            else{
                if (findParent(a) != findParent(b)) cout << "UNKNOWN\n";
                else cout << dist[a] - dist[b] << "\n";
            }
        }
    }

    return 0;
}