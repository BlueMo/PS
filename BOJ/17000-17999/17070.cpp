#include <iostream>
#include <algorithm>
using namespace std;

int N, D[2], k;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> N;

    D[1] = 1;
    for (int i = 2; i <= N; i++, k = !k){
        D[k] += D[!k];
    }
    cout << D[!k];
}