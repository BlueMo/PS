#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

typedef pair<int, int> pii;
typedef pair<int, pii> piii;

int N, Q, x, a, b, par[200001];
vector<piii> query;
vector<string> ans;

int findParent(int u){
    if (u == par[u]) return u;
    return par[u] = findParent(par[u]);
}

void unionSet(int u, int v){
    u = findParent(u), v = findParent(v);

    par[v] = u;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> N >> Q;
    par[1] = 1;
    for (int i = 2; i <= N; i++){
        cin >> a;
        par[i] = a;
    }

    for (int i = 0; i < N - 1 + Q; i++){
        cin >> x >> a;
        
        if (!x){
            query.push_back({x, {par[a], a}});
            par[a] = a;
        }
        else{
            cin >> b;
            query.push_back({x, {a, b}});
        }
    }

    for (int i = query.size() - 1; i >= 0; i--){
        x = query[i].first;
        a = query[i].second.first, b = query[i].second.second;

        if (!x) unionSet(a, b);
        else{
            if (findParent(a) == findParent(b)) ans.push_back("YES");
            else ans.push_back("NO");
        }
    }
    
    for (int i = ans.size() - 1; i >= 0; i--){
        cout << ans[i] << "\n";
    }

    return 0;
}