#include <iostream>
#include <algorithm>
using namespace std;
 
int N, M, treeBase = 1, a, b;
int segTree[1<<18];
 
int getMin(int u, int v){
	if (u > v) swap(u, v);
    int l = treeBase + u - 1;
    int r = treeBase + v - 1;
 
    int ret = 0x7fffffff;
    while (l <= r){
        if (l & 1){
            ret = min(ret, segTree[l++]);
        }
        if (~r & 1){
            ret = min(ret, segTree[r--]);
        }
        l >>= 1, r >>= 1;
    }
    return ret;
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
 
    cin >> N >> M;
    while (treeBase < N) treeBase <<= 1;
    for (int i = treeBase; i < treeBase + N; i++){
        cin >> segTree[i];
    }
	for (int i = treeBase + N; i < (treeBase << 1); i++){
		segTree[i] = 0x7fffffff;
	}
    for (int i = treeBase - 1; i >= 1; i--){
        segTree[i] = min(segTree[i << 1], segTree[(i << 1) | 1]);
    }
 
    while (M--){
        cin >> a >> b;
        cout << getMin(a, b) << "\n";
    }
    return 0;
}