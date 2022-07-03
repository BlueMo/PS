#include <iostream>
#include <algorithm>
using namespace std;

int N, M, v[10], a[10];
bool chk[10];

void sol(int n, int m){
    if (m == M){
        for (int i = 0; i < m; i++){
            cout << v[i] << " ";
        }cout << "\n";
        return;
    }
    for (int i = 0; i < N; i++){
        if (chk[i]) continue;
        chk[i] = 1;
        v[m] = a[i];
        sol(i, m + 1);
        chk[i] = 0;
    }
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> N >> M;
    for (int i = 0; i < N; i++){
        cin >> a[i];
    }
    sort(a, a + N);
    sol(-1, 0);
    return 0;
}