#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;

int N, A[1000001], ans[1000001];
stack<int> s;
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> N;
    for (int i = 0; i < N; ++i){
        ans[i] = -1;
        cin >> A[i];

        while(!s.empty()){
            int h = s.top();
            if (A[h] >= A[i]) break;
            ans[h] = A[i];
            s.pop();
        }
        s.push(i);
    }

    for (int i = 0; i < N-1; ++i) cout << ans[i] << " ";
    cout << -1;
    return 0;
}