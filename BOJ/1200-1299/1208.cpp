#include <iostream>
#include <algorithm>
using namespace std;

int N, S, a[1000001];
long long s[2][5000001];
long long ans;

void seqCombination(int n, int m, int sum, int idx){
    if (!n){
        s[idx][sum + 2000000]++;
        return;
    }
    seqCombination(n-1, m+1, sum + a[m], idx);
    seqCombination(n-1, m+1, sum, idx);
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> N >> S;
    for (int i = 0; i < N; ++i) cin >> a[i];

    seqCombination(N/2, 0, 0, 0);
    seqCombination(N - N/2, N/2, 0, 1);

    for (int i = 0; i <= 4000000; ++i){
        if (!s[0][i]) continue;
        ans += s[0][i] * s[1][S - i + 4000000];
    }

    if (S) cout << ans;
    else cout << ans-1;
    return 0;
}