#include <iostream>
#include <algorithm>
using namespace std;
typedef pair<int, int> pii;

struct P{
    pii u, v;
}a[3001];
int N, p[3001], r[3001], cntGroup, maxSize;

int ccw(pii a, pii b, pii c){
    int ret = a.first*b.second + b.first*c.second + c.first*a.second 
            -(a.first*c.second + b.first*a.second + c.first*b.second);

    if (ret > 0) return 1;
    if (ret < 0) return -1;
    return 0;
}
bool isIntersect(P a, P b){
    int ccw1 = ccw(a.u, a.v, b.u) * ccw(a.u, a.v, b.v);
    int ccw2 = ccw(b.u, b.v, a.u) * ccw(b.u, b.v, a.v);

    if (!ccw1 && !ccw2) return a.u <= b.v && b.u <= a.v;
    else return ccw1 <= 0 && ccw2 <= 0;
}
int find_parent(int u){
    if (p[u] == u) return u;
    return p[u] = find_parent(p[u]);
}
void Union_set(int u, int v){
    u = find_parent(u);
    v = find_parent(v);
    
    if (u == v) return;
    p[v] = u;
    r[u] += r[v];
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; ++i){
        cin >> a[i].u.first >> a[i].u.second >> a[i].v.first >> a[i].v.second;
        r[i] = 1;
        p[i] = i;

        if (a[i].u > a[i].v) swap(a[i].u, a[i].v);
    }

    for (int i = 1; i <= N; ++i){
        for (int j = i+1; j <= N; ++j){
            if (!isIntersect(a[i], a[j])) continue;
            Union_set(i, j);
        }
    }

    for (int i = 1; i <= N; ++i){
        if (p[i] != i) continue;
        cntGroup++;
        maxSize = max(maxSize, r[i]);
    }
    cout << cntGroup << "\n" << maxSize;
    return 0;
}