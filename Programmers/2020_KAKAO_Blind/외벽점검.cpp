#include <string>
#include <vector>
#include <algorithm>
#define INF 0x7fffffff
using namespace std;

int solution(int n, vector<int> weak, vector<int> dist) {
    int answer = INF, m = weak.size();
    for (int i = 0; i < m; i++) weak.push_back(weak[i] + n);
    sort(dist.begin(), dist.end());
    do{
        for (int i = 0; i < m; i++){
            int idx = i;
            for (int j = 0; j < dist.size(); j++){
                idx = upper_bound(weak.begin(), weak.end(), weak[idx] + dist[j]) - weak.begin();
                if (idx >= i + m){
                    answer = min(answer, j+1);
                    break;
                }
            }
        }
    }while(next_permutation(dist.begin(), dist.end()));
    return (answer != INF) ? answer : -1;
}
int main(){ return 0; }