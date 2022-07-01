#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;

const ll MOD = 1e9+7;
ll n, m[2][2] = {{0, 1}, {1, 1}}, ans[2][2] = {{1, 0}, {0, 1}}, tmp[2][2];
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    if (n == 1){
        cout << 1;
        return 0;
    }
    n -= 2;
    while (n){
        if (n % 2){
            for (int i = 0; i < 2; i++){
                for (int j = 0; j < 2; j++){
                    tmp[i][j] = 0;
                    for (int k = 0; k < 2; k++){
                        tmp[i][j] = (tmp[i][j] + (ans[i][k] * m[k][j]) % MOD) % MOD;
                    }
                }
            }
            memcpy(ans, tmp, sizeof(ans));
        }
        for (int i = 0; i < 2; i++){
            for (int j = 0; j < 2; j++){
                tmp[i][j] = 0;
                for (int k = 0; k < 2; k++){
                    tmp[i][j] = (tmp[i][j] + (m[i][k] * m[k][j]) % MOD) % MOD;
                }
            }
        }
        memcpy(m, tmp, sizeof(m));
        n >>= 1;
    }

    cout << (ans[1][0] + ans[1][1]) % MOD;
    return 0;
}
