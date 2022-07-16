#include <iostream>
#include <algorithm>
using namespace std;

int D[2][3], D2[2][3], N;
bool k = 0;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> N;
    for (int i = 0; i < 3; i++){
        cin >> D[k][i];
        D2[k][i] = D[k][i];
    }

    for (int i = 1; i < N; i++){
        k = !k;
        for (int j = 0; j < 3; j++){
            cin >> D[k][j];
            D2[k][j] = D[k][j];
        }
        D[k][0] += max(D[!k][0], D[!k][1]);
        D[k][1] += max({D[!k][0], D[!k][1], D[!k][2]});
        D[k][2] += max(D[!k][1], D[!k][2]);

        D2[k][0] += min(D2[!k][0], D2[!k][1]);
        D2[k][1] += min({D2[!k][0], D2[!k][1], D2[!k][2]});
        D2[k][2] += min(D2[!k][1], D2[!k][2]);
    }

    cout << max({D[k][0], D[k][1], D[k][2]}) << " " << 
            min({D2[k][0], D2[k][1], D2[k][2]});
    return 0;  
}