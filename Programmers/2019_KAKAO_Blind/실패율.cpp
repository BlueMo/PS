#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> solution(int N, vector<int> stages) {
    vector<int> answer;
    vector<pair<double, int>> rate;
    int m = stages.size();
    for (auto &i : stages) i *= -1; 
    sort(stages.begin(), stages.end());
    stages.push_back(0);
    int prev = lower_bound(stages.begin(), stages.end(), -N) - stages.begin(), idx;
    for (int i = N; i > -stages[prev]; i--) rate.push_back({0, i});
    while (prev != m){
        idx = lower_bound(stages.begin(), stages.end(), stages[prev]+1) - stages.begin();
        for (int i = -stages[prev]-1; i > -stages[idx]; i--) rate.push_back({0, i});
        rate.push_back({(double)(prev - idx) / idx, -stages[prev]});
        prev = idx;
    }
    sort(rate.begin(), rate.end());
    for (auto i : rate) answer.push_back(i.second);
    return answer;
}

int main(){ return 0; }