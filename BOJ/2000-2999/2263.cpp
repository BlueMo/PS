#include <iostream>
#include <algorithm>
#include <deque>
using namespace std;

#define MAX_N 100001

int n, inOrder[MAX_N], inIdx[MAX_N], postOrder[MAX_N];
int ans[MAX_N], ansIdx;

void sol(int l1, int r1, int l2, int r2){
    if (l1 > r1 || l2 > r2) return;
    cout << postOrder[r2] << " ";
    int idx = inIdx[postOrder[r2]];
    int t = idx - l1;
    
    sol(l1, idx - 1, l2, l2 + t - 1);
    sol(idx + 1, r1, l2 + t, r2 - 1);
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++){
        cin >> inOrder[i];
        inIdx[inOrder[i]] = i;
    }
    for (int i = 0; i < n; i++){
        cin >> postOrder[i];
    }

    sol(0, n - 1, 0, n - 1);
    return 0;
}