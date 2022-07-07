#include <iostream>
#include <algorithm>
using namespace std;

#define MAX_N 1100
int N, M, D[MAX_N][MAX_N], x1, x2, y1, y2;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> N >> M;
    for (int i = 1; i <= N; i++){
        for (int j = 1; j <= N; j++){
            cin >> D[i][j];
            D[i][j] += D[i-1][j] + D[i][j-1] - D[i-1][j-1];
        }
    }

    while (M--){
        cin >> x1 >> y1 >> x2 >> y2;
        cout << D[x2][y2] - D[x2][y1 - 1] - D[x1 - 1][y2] + D[x1 - 1][y1 - 1] << "\n";
    }

    return 0;
}