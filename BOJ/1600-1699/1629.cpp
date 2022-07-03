#include <iostream>
#include <algorithm>
using namespace std;

long long A, B, C, ans = 1;
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> A >> B >> C;
    while (B){
        if (B % 2) ans = (ans * A) % C;

        A = (A * A) % C;
        B >>= 1;
    }
    cout << ans;
    return 0;
}