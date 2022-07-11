#include <iostream>
#include <algorithm>
using namespace std;
typedef pair<int, int> pii;

#define MAX_W 1002
#define INF 0x7fffffff

int N, W, y[MAX_W], x[MAX_W], minIdx, D[MAX_W][MAX_W], dist, a, b, path[MAX_W];
pii v[MAX_W][MAX_W];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> N >> W;
    
    x[0] = y[0] = 1;
    for (int i = 1; i <= W; i++){
        cin >> y[i] >> x[i];
    }
    for (int i = 0; i <= W; i++){
        for (int j = 0; j <= W; j++){
            D[i][j] = INF;
        }
    }

    D[0][1] = abs(N - x[1]) + abs(N - y[1]);
    D[1][0] = abs(1 - x[1]) + abs(1 - y[1]);
    v[0][1] = {0, 2};
    v[1][0] = {0, 1};

    for (int i = 2; i <= W; i++){
        for (int j = 0; j < i - 1; j++){
            dist = abs(x[i - 1] - x[i]) + abs(y[i - 1] - y[i]);
            D[i][j] = D[i - 1][j] + dist;
            v[i][j] = {i - 1, 1};
            D[j][i] = D[j][i - 1] + dist;
            v[j][i] = {i - 1, 2};

            dist = abs(x[j] - x[i]) + abs(y[j] - y[i]);
            if (D[i][i - 1] > D[j][i - 1] + dist){
                D[i][i - 1] = D[j][i - 1] + dist;
                v[i][i - 1] = {j, 1};
            }
            if (j == 0) dist = abs(N - x[i]) + abs(N - y[i]);
            if (D[i - 1][i] > D[i - 1][j] + dist){
                D[i - 1][i] = D[i - 1][j] + dist;
                v[i - 1][i] = {j, 2};
            }
        }
    }
    
    a = W;
    b = 0;
    for (int i = 0; i < W; i++){
        if (D[a][b] > D[W][i]){
            a = W;
            b = i;
        }
        if (D[a][b] > D[i][W]){
            a = i;
            b = W;
        }
    }

    cout << D[a][b] << "\n";
    for (int i = W; i >= 1; i--){
        path[i] = v[a][b].second;
        if (path[i] == 1){
            a = v[a][b].first;
        }
        else{
            b = v[a][b].first;
        }
    }
    for (int i = 1; i <= W; i++){
        cout << path[i] << "\n";
    }
    return 0;
}