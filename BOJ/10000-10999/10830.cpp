#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long ll;

#define MAX_N 6

int N, A[MAX_N][MAX_N], ans[MAX_N][MAX_N], tmp[MAX_N][MAX_N];
ll B;
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> N >> B;
    for (int i = 0; i < N; i++){
        ans[i][i] = 1;
        for (int j = 0; j < N; j++){
            cin >> A[i][j];
        }
    }

    while (B){
        if (B & 1){
            for (int i = 0; i < N; i++){
                for (int j = 0; j < N; j++){
                    tmp[i][j] = 0;
                    for (int k = 0; k < N; k++){
                        tmp[i][j] = (tmp[i][j] + (ans[i][k] * A[k][j]) % 1000) % 1000; 
                    }
                }
            }
            memcpy(ans, tmp, sizeof(ans));
        }
        for (int i = 0; i < N; i++){
            for (int j = 0; j < N; j++){
                tmp[i][j] = 0;
                for (int k = 0; k < N; k++){
                    tmp[i][j] = (tmp[i][j] + (A[i][k] * A[k][j]) % 1000) % 1000; 
                }
            }
        }
        memcpy(A, tmp, sizeof(A));
        B >>= 1;
    }
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            cout << ans[i][j] << " ";
        }cout << "\n";
    }
    return 0;
}