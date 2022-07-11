#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
typedef pair<int, int> pii;

#define MAX_N 100001

int n, d, ans;
pii p[MAX_N];
priority_queue<int, vector<int>, greater<int>> pq;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++){
        cin >> p[i].first >> p[i].second;
        if (p[i].first < p[i].second) swap(p[i].first, p[i].second);
    }
    cin >> d;
    
    sort(p, p + n);
    for (int i = 0; i < n; i++){
        if (p[i].first - p[i].second > d) continue;
        pq.push(p[i].second);

        while (!pq.empty()){
            int h = pq.top();
            if (h < p[i].first - d) pq.pop();
            else break;
        }
        ans = max(ans, (int)pq.size());
    }
    cout << ans;
    return 0;
}