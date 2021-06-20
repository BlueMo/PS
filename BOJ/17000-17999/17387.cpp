#include <iostream>
#include <algorithm>
using namespace std;
typedef pair<long long, long long> pll;

struct L{
    pll u, v;
}a[2];
long long ccw1, ccw2;
bool ans;

int ccw(pll a, pll b, pll c){
    long long ret = a.first*b.second + b.first*c.second + c.first*a.second
            -(a.first*c.second + b.first*a.second + c.first*b.second);

    if (ret < 0) return -1;
    if (ret > 0) return 1;
    return 0;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    for (int i = 0; i < 2; ++i){
        cin >> a[i].u.first >> a[i].u.second >> a[i].v.first >> a[i].v.second;
        if (a[i].u > a[i].v) swap(a[i].u, a[i].v);
    }

    ccw1 = ccw(a[0].u, a[0].v, a[1].u) * ccw(a[0].u, a[0].v, a[1].v);
    ccw2 = ccw(a[1].u, a[1].v, a[0].u) * ccw(a[1].u, a[1].v, a[0].v);

    if (!ccw1 && !ccw2) ans = (a[0].u <= a[1].v && a[1].u <= a[0].v);
    else ans = (ccw1 <= 0 && ccw2 <= 0);

    cout << ans;
    return 0;
}