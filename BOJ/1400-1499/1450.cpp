#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int N, C, w[31], cnt, ans;
vector<int> a[2];
void f(int n, int weight, int m, int t){
    if (!m){
        a[t].push_back(weight);
        return;
    }

    if (weight + w[n] <= C) f(n-1, weight + w[n], m-1, t);
    f(n-1, weight, m-1, t);
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> N >> C;
    for (int i = 1; i <= N; ++i) cin >> w[i];

    f(N/2, 0, N/2, 0);
    f(N, 0, N-N/2, 1);

    sort(a[0].begin(), a[0].end());
    sort(a[1].begin(), a[1].end());

    for (auto &i : a[0]) ans += upper_bound(a[1].begin(), a[1].end(), C - i) - a[1].begin();
    cout << ans;
    return 0;
}
