#include <iostream>
#include <algorithm>
using namespace std;

int N, a[20][20], D[20][20][3];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> N;
    for (int i = 1; i <= N; i++) for (int j = 1; j <= N; j++) cin >> a[i][j];

    D[1][2][0] = 1;
    for (int i = 1; i <= N; i++){
        for (int j = 1; j <= N; j++){
            if (a[i][j]) continue;

            D[i][j][0] += D[i][j - 1][0] + D[i][j - 1][2];
            D[i][j][1] += D[i - 1][j][1] + D[i - 1][j][2];
            if (!a[i - 1][j] && !a[i][j - 1]) D[i][j][2] += D[i - 1][j - 1][0] + D[i - 1][j - 1][1] + D[i - 1][j - 1][2];
        }
    }

    cout << D[N][N][0] + D[N][N][1] + D[N][N][2];

    return 0;
}