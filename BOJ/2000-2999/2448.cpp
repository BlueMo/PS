#include <iostream>
using namespace std;

int N;
char c[3 * 1024 + 1][6 * 1024 + 1];

void sol(int y, int x, int n){
    if (n == 1) y--;
    for (int i = 0; i < n; i++){
        for (int j = -i; j <= i; j++){
            c[y - i][x + j] = ' ';
        }
    }
    if (n == 1) return;
    sol(y, x - n, n >> 1);
    sol(y, x + n, n >> 1);
    sol(y - n, x, n >> 1);
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> N;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N - i - 1; j++){
            c[i][j] = ' ';
        }
        for (int j = N - i - 1; j < N + i; j++){
            c[i][j] = '*';
        }
        for (int j = N + i; j < N << 1; j++){
            c[i][j] = ' ';
        }
    }

    sol(N - 1, N - 1, N >> 1);

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N << 1; j++){
            cout << c[i][j];
        }cout << "\n";
    }
    return 0;
}
