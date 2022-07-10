#include <iostream>
#include <algorithm>
using namespace std;

int N, col, diag1, diag2;
int sol(int y){
    if (y == N) return 1;

    int ret = 0;
    for (int x = 0; x < N; x++){
        if ((col & (1 << x)) || (diag1 & (1 << (N - x + y))) || (diag2 & (1 << (x + y)))) continue;
        col |= 1 << x;
        diag1 |= 1 << (N - x + y);
        diag2 |= 1 << (x + y);

        ret += sol(y + 1);

        col ^= 1 << x;
        diag1 ^= 1 << (N - x + y);
        diag2 ^= 1 << (x + y);
    }

    return ret; 
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> N;

    cout << sol(0);
    return 0;
}