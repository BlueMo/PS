#include <iostream>
#include <algorithm>
using namespace std;

int inOrder[10002], idx, N;

void sol(int l, int r){
    int cur = inOrder[idx];
    idx++;
    if (inOrder[idx] < cur && inOrder[idx] > l){
        sol(l, cur);
    }
    if (inOrder[idx] > cur && inOrder[idx] < r){
        sol(cur, r);
    }
    printf("%d\n", cur);
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    while (cin >> inOrder[N++]);

    sol(0, 1e7);
}