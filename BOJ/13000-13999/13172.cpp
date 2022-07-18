#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

int M, p;
ll N, S, ans, b;
const int X = 1e9 + 7;
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> M;
    while(M--){
        cin >> N >> S;
        p = X - 2;
        b = 1LL;
        while (p){
            if (p & 1) b = (b * N) % X;
            N = (N * N) % X;
            p >>= 1;
        }
        ans = (ans + (S * b) % X) % X;
    }

    cout << ans;

    return 0;
}