#include <iostream>
#include <algorithm>
using namespace std;

int N, M, v[10];

void sol(int n, int m){
    if (m == M){
        for (int i = 0; i < m; i++){
            cout << v[i] << " ";
        }cout << "\n";
        return;
    }
    for (int i = n + 1; i <= N; i++){
        v[m] = i;
        sol(i, m + 1);
    }
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> N >> M;

    sol(0, 0);
    return 0;
}