#include <string>
#include <vector>
#include <algorithm>
#include <tuple>
#include <iostream>
using namespace std;
typedef tuple<int, int, int> tiii;
typedef pair<int, int> pii;
vector<tiii> nodeinfo2;
vector<vector<pii>> height;
vector<int> preOrder, postOrder;
void DFS(int h, int p, int l, int r){
    preOrder.push_back(height[h][p].second);
    if (h == height.size()-1) return; 
    for (int i = 0; i < height[h+1].size(); i++){
        auto [x, idx] = height[h+1][i];
        if (x > l && x < r){
            if (x > height[h][p].first){
                DFS(h+1, i, height[h][p].first, r);
                postOrder.push_back(idx);
            }
            else{
                DFS(h+1, i, l, height[h][p].first);
                postOrder.push_back(idx);
            }
        }
    }
}
vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
    int n = nodeinfo.size();
    vector<vector<int>> answer;
    vector<vector<int>> adj(n, vector<int>(2, -1));
        
    for (int i = 0; i < n; i++) nodeinfo2.push_back({nodeinfo[i][1], nodeinfo[i][0], i+1});
    sort(nodeinfo2.begin(), nodeinfo2.end(), 
         [](tiii &a, tiii &b){
             if (get<0>(a) != get<0>(b)) return get<0>(a) > get<0>(b);
             return get<1>(a) < get<1>(b);
         });
    vector<pii> vec_pii;
    height.push_back(vec_pii);
    height[0].push_back({get<1>(nodeinfo2[0]), get<2>(nodeinfo2[0])});
    int prev = get<0>(nodeinfo2[0]), h = 0;
    for (int i = 1; i < n; i++){
        auto [y, x, idx] = nodeinfo2[i];
        if (y != prev){
            h++;
            height.push_back(vec_pii);
        }
        height[h].push_back({x, idx});
        prev = y;
    }
    
    DFS(0, 0, -1, 100001);
    postOrder.push_back(height[0][0].second);
    answer.push_back(preOrder);
    answer.push_back(postOrder);
    return answer;
}
int main(){ return 0;}