#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#define MAX_SIZE 51

int N, M, par[MAX_SIZE], c, a, b, ans;
vector<int> party[MAX_SIZE];
bool chk[MAX_SIZE];

int findParent(int u){
    if (u == par[u]) return u;
    return par[u] = findParent(par[u]);
}

void unionSet(int u, int v){
    u = findParent(u);
    v = findParent(v);
    par[v] = u;
    chk[u] |= chk[v];
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> N >> M;
    cin >> c;
    for (int i = 0; i < c; i++){
        cin >> a;
        chk[a] = 1;
    }
    for (int i = 1; i <= N; i++){
        par[i] = i;
    }
    for (int i = 0; i < M; i++){
        cin >> c;
        cin >> a;
        party[i].push_back(a);
        for (int j = 1; j < c; j++){
            cin >> b;
            party[i].push_back(b);
            unionSet(a, b);
        }
    }

    for (int i = 0; i < M; i++){
        a = party[i][0];
        if (!chk[findParent(a)]) ans++;
    }

    cout << ans;
    return 0;
}