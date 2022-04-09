#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int N;
vector<vector<int>> cost, D;
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> N;
    cost.resize(N+1, vector<int>(3, 0));
    D.resize(N+1, vector<int>(3, 0));
    for (int i = 1; i <= N; i++){
        for (int j = 0; j < 3; j++){
            cin >> cost[i][j];
        }
    }

    for (int i = 1; i <= N; i++){
        for (int j = 0; j < 3; j++){
            D[i][j] = min(D[i-1][(j+1)%3], D[i-1][(j+2)%3]) + cost[i][j];
        }
    }

    cout << min({D[N][0], D[N][1], D[N][2]});
    return 0;
}