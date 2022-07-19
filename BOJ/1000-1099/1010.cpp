#include <iostream>
using namespace std;

int T, N, M, D[30][30];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> T;
    D[0][0] = 1;
    for (int i = 1; i < 30; i++){
        D[i][0] = D[i][i] = 1;
        for (int j = 1; j < i; j++){
            D[i][j] = D[i-1][j-1] + D[i-1][j];
        }
    }
    while (T--){
        cin >> N >> M;
        cout << D[M][N] << "\n";
    }
    return 0;
}