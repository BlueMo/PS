#include <iostream>
#include <algorithm>
using namespace std;

int n, m, r, t[101], dist[101][101], a, b, c, ans, sum;
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n >> m >> r;
    for (int i = 1; i <= n; i++) cin >> t[i];
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            dist[i][j] = 1e9;
        }
        dist[i][i] = 0;
    }
    for (int i = 1; i <= r; i++){
        cin >> a >> b >> c;
        dist[a][b] = dist[b][a] = c;
    }
    for (int k = 1; k <= n; k++){
        for (int i = 1; i <= n; i++){
            for (int j = 1; j <= n; j++){
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    for (int i = 1; i <= n; i++){
        sum = 0;
        for (int j = 1; j <= n; j++){
            if (dist[i][j] <= m) sum += t[j];
        }
        ans = max(ans, sum);
    }

    cout << ans;
    return 0;
}