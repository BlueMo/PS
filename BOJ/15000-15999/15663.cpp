#include <iostream>
#include <algorithm>
using namespace std;

#define MAX_M 8

int N, M, v[MAX_M + 1], a[MAX_M + 1];
bool chk[MAX_M + 1];

void sol(int m){
    if (m == M){
        for (int i = 0; i < M; i++){
            cout << v[i] << " ";
        }cout << "\n";
        
        return;
    }
    int tmp = -1;

    for (int i = 0; i < N; i++){
        if (chk[i]) continue;
        if (tmp == a[i]) continue;
        v[m] = a[i];
        tmp = a[i];
        chk[i] = 1;
        sol(m + 1);
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
    sol(0);
    return 0;
}