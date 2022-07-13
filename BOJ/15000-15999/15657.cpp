#include <iostream>
#include <algorithm>
using namespace std;

#define MAX_M 8

int N, M, v[MAX_M + 1], a[MAX_M + 1];

void sol(int n, int m){
    if (m == M){
        for (int i = 0; i < M; i++){
            cout << v[i] << " ";
        }cout << "\n";
        
        return;
    }
    for (int i = n; i < N; i++){
        v[m] = a[i];
        sol(i, m + 1);
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
    sol(0, 0);
    return 0;
}