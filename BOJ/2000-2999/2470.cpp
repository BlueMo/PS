#include <iostream>
#include <algorithm>
using namespace std;

int N, a[100001], l, r, minSum = 0x7fffffff, x, y; 
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> N;
    for (int i = 0; i < N; ++i) cin >> a[i];
    sort(a, a+N);    

    l = 0, r = N-1;
    while (l < r){
        int sum = abs(a[l] + a[r]);
        if (minSum > sum){
            minSum = sum;
            x = a[l];
            y = a[r];
        }
        if (a[l] + a[r] < 0) l++;
        else r--;
    }
    cout << x << " " << y;
    return 0;
}