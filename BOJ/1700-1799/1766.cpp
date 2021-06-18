#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

int N, M, A, B, par[32001];
vector<int> son[32001];
priority_queue<int, vector<int>, greater<int>> pq;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    cin >> N >> M;

    for (int i = 0; i < M; ++i){
        cin >> A >> B;
        son[A].push_back(B);
        par[B]++;
    }

    for (int i = 1; i <= N; ++i){
        if (!par[i]) pq.push(i);
    }

    while (!pq.empty()){
        int h = pq.top();
        pq.pop();
        cout << h << " ";
        
        for (auto &i : son[h]){
            par[i]--;
            if (!par[i]) pq.push(i);
        }
    }
    return 0;
}