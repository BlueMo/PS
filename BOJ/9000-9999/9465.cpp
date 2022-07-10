#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

#define MAX_N 100001
int T, n, a[2][MAX_N], D[2][MAX_N], ans;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    while (T--){
        cin >> n;
        for (int i = 0; i < 2; i++){
            for (int j = 1; j <= n; j++){
                cin >> a[i][j];
            }
        }
        D[0][0] = D[1][0] = 0;
        D[0][1] = a[0][1];
        D[1][1] = a[1][1];
        ans = max(D[0][1], D[1][1]);
        for (int i = 2; i <= n; i++){
            D[0][i] = max({D[0][i-2], D[1][i-1], D[1][i-2]}) + a[0][i];
            D[1][i] = max({D[1][i-2], D[0][i-1], D[0][i-2]}) + a[1][i];
            ans = max({ans, D[0][i], D[1][i]});
        }
        cout << ans << "\n";
    }
    return 0;
}