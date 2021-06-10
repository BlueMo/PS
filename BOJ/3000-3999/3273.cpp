#include <iostream>
#include <algorithm>
using namespace std;

int n, x, a, ans;
bool cnt[1000001];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 0; i < n; ++i){
        cin >> a;
        cnt[a] = 1;
    }
    cin >> x;

    for (int i = 1; i <= x/2; ++i){
        if (x - i > 1000000 || i == x-i) continue;
        ans += cnt[i] & cnt[x-i];
    }
    cout << ans;
}