#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
typedef pair<long long, int> pli;

int solution(vector<int> food_times, long long k) {
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    
    for (int i = 0; i < food_times.size(); i++) pq.push({food_times[i], i+1});
    long long a = 0;
    k++;
    while (!pq.empty()){
        int n = pq.size();
        auto [t, idx] = pq.top();
        t -= a;
        if (!t){
            pq.pop();
            continue;
        }
        if (k > t * n){
            k -= t * n;
            a += t;
            pq.pop();
        }
        else{
            k %= n;
            if (!k) k = n;
            break;
        }
    }
    if (pq.size() == 0) return -1;
    vector<int> foods;
    while (!pq.empty()){
        foods.push_back(pq.top().second);
        pq.pop();
    }
    sort(foods.begin(), foods.end());
    return foods[k-1];
}
int main(){ return 0; }