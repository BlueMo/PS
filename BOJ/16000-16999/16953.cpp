#include <iostream>
using namespace std;

int A, B, ans;
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> A >> B;
    
    while (A < B){
        if (B & 1){
            if (B % 10 == 1) B /= 10;
            else{
                cout << -1;
                return 0;
            }
        }
        else B >>= 1;
        ans++;
    }
    if (A == B) cout << ans + 1;
    else cout << -1;

    return 0;
}