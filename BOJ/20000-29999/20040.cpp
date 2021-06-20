#include <iostream>
#include <algorithm>
using namespace std;

int n, m, a, b, p[500001];

int findParent(int u){
    if (p[u] == u) return u;
    return p[u] = findParent(p[u]);
}
bool unionSet(int u, int v){
    u = findParent(u);
    v = findParent(v);
    if (u == v) return 0;
    p[v] = u;
    return 1;
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m;
    for (int i = 0; i < n; ++i) p[i] = i;
    
    for (int i = 1; i <= m; ++i){
        cin >> a >> b;
        if (!unionSet(a, b)){
            cout << i;
            return 0;
        }
    }

    cout << 0;
    return 0;
}